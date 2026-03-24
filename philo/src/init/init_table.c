/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:27:32 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/24 20:52:56 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Inicializamos los mutex
static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->death_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL))
	{
		pthread_mutex_destroy(&table->death_mutex);
		return (1);
	}
	if (pthread_mutex_init(&table->meal_mutex, NULL))
	{
		pthread_mutex_destroy(&table->death_mutex);
		pthread_mutex_destroy(&table->print_mutex);
		return (1);
	}
	return (0);
}

//Inicializamos la mesa
int	init_table(t_table *table)
{
	table->someone_died = false;
	table->simulation_finished = false;
	table->forks = NULL;
	table->philos = NULL;
	if (init_mutexes(table))
		return (1);
	table->start_time = get_time_ms();
	return (0);
}
