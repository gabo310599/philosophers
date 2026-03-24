/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:56:20 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/24 20:09:16 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Obtenemos el mensaje a imprimir
static char	*get_state_msg(t_state state)
{
	if (state == TAKEN_FORK)
		return ("has taken a fork");
	if (state == EATING)
		return ("is eating");
	if (state == SLEEPING)
		return ("is sleeping");
	if (state == THINKING)
		return ("is thinking");
	if (state == DIED)
		return ("died");
	return ("");
}

//Obtenemos el color asociado al estado
static char	*get_state_color(t_state state)
{
	if (state == TAKEN_FORK)
		return (C_FORK);
	if (state == EATING)
		return (C_EAT);
	if (state == SLEEPING)
		return (C_SLEEP);
	if (state == THINKING)
		return (C_THINK);
	if (state == DIED)
		return (C_DIE);
	return (C_RESET);
}

//Imprimimos el estado
void	print_state(t_philo *philo, t_state state)
{
	long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (state != DIED && simulation_stopped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	time = timestamp(philo->table);
	printf("%s%ld %d %s%s\n",
		get_state_color(state),
		time,
		philo->id,
		get_state_msg(state),
		C_RESET);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
