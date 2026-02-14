/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:59:36 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:04:00 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Verificamos si alguno philo murio
static int	check_death(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->table->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	now = get_time_ms();
	if ((now - last_meal) >= philo->table->time_to_die)
	{
		print_state(philo, DIED);
		pthread_mutex_lock(&philo->table->death_mutex);
		philo->table->someone_died = true;
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	return (0);
}

//Verificamos las comidas en caso de que pasen 6 args
static int	check_meals(t_table *table)
{
	int	i;
	int	finished;

	if (!table->must_eat_flag)
		return (0);
	i = 0;
	finished = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->philos[i].meals_eaten
			>= table->must_eat_count)
			finished++;
		pthread_mutex_unlock(&table->meal_mutex);
		i++;
	}
	if (finished == table->num_philos)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->someone_died = true;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

//Rutina del monitor
void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!simulation_stopped(table))
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (check_death(&table->philos[i]))
				return (NULL);
			i++;
		}
		if (check_meals(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
