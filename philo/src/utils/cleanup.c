/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:18:08 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:19:28 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Destruimos los mutex de los tenedores
static void	destroy_forks(t_table *table)
{
	int	i;

	if (!table->forks)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

//Destruimos los mutex generales
static void	destroy_global_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
}

//Funcion de control de limpieza
void	cleanup(t_table *table)
{
	destroy_forks(table);
	destroy_global_mutexes(table);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}