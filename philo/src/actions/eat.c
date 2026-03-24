/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:22 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/24 21:36:13 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Bloqueamos el mutex de los tenedores
static int	lock_forks(t_philo *philo)
{
	while (!simulation_stopped(philo->table))
	{
		if (philo->id % 2 == 0)
		{
			if (pthread_mutex_trylock(philo->right_fork) == 0)
			{
				print_state(philo, TAKEN_FORK);
				if (pthread_mutex_trylock(philo->left_fork) == 0)
				{
					print_state(philo, TAKEN_FORK);
					return (0);
				}
				pthread_mutex_unlock(philo->right_fork);
			}
		}
		else
		{
			if (pthread_mutex_trylock(philo->left_fork) == 0)
			{
				print_state(philo, TAKEN_FORK);
				if (pthread_mutex_trylock(philo->right_fork) == 0)
				{
					print_state(philo, TAKEN_FORK);
					return (0);
				}
				pthread_mutex_unlock(philo->left_fork);
			}
		}
		usleep(100);
	}
	return (1);
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
	if (simulation_stopped(philo->table))
		return ;
	if (lock_forks(philo))
		return ;
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	precise_sleep(philo->table->time_to_eat, philo->table);
	unlock_forks(philo);
}
