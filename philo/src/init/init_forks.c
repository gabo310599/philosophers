/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:33:34 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:34:52 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Inicializamos los mutexes para los tenedores
static int	init_fork_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->forks);
			table->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

//Inicializamos los tenedores
int	init_forks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->num_philos);
	if (!table->forks)
		return (1);
	if (init_fork_mutexes(table))
		return (1);
	return (0);
}
