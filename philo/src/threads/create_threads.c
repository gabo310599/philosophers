/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:41:00 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:42:48 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Creamos los hilos de los philos
static int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread,
				NULL, philo_routine, &table->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

//Creamos el hilo del monitor
static int	create_monitor_thread(t_table *table)
{
	if (pthread_create(&table->monitor_thread,
			NULL, monitor_routine, table))
		return (1);
	return (0);
}

//Creamos los hilos (funcion de control)
int	create_threads(t_table *table)
{
	if (create_philo_threads(table))
		return (1);
	if (create_monitor_thread(table))
		return (1);
	return (0);
}

//Unimos los hilos creados
void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}
