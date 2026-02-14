/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:11:20 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:12:27 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Paramos la simulacion
int	simulation_stopped(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->death_mutex);
	stop = table->someone_died;
	pthread_mutex_unlock(&table->death_mutex);
	return (stop);
}

//Matamos un philo
void	set_death(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->someone_died = true;
	pthread_mutex_unlock(&table->death_mutex);
}