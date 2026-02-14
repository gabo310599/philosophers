/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:52:21 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:53:45 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Dormimos
void	philo_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	precise_sleep(philo->table->time_to_sleep, philo->table);
}
