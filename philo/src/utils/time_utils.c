/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:30:36 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:16:36 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Obtenemos tiempo en ms
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

//Devolvemos un timestamp
long	timestamp(t_table *table)
{
	return (get_time_ms() - table->start_time);
}

//Mandamos a dormir el hilo si es necesario
void	precise_sleep(long time, t_table *table)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time)
	{
		if (simulation_stopped(table))
			break ;
		usleep(500);
	}
}
