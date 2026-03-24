/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:46:57 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/24 21:06:06 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Desfasamos el inicio de los philos pares
static void	stagger_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000 + (philo->id * 10));
}

//Manejamos caso de un philo
static void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, TAKEN_FORK);
	precise_sleep(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
}

//Rutina de philo
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philos == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	stagger_start(philo);
	while (!simulation_stopped(philo->table))
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}