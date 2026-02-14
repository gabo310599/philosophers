/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:22 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:50:49 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Bloqueamos el mutex de los tenedores
static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, TAKEN_FORK);
	}
}

//Desbloqueamos el mutex de los tenedores
static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

//Control y accion de comer de philo
void	eat(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	precise_sleep(philo->table->time_to_eat, philo->table);
	unlock_forks(philo);
}
