/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:27:59 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:28:25 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"


void	safe_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		error_exit("Mutex lock failed\n");
}

void	safe_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
		error_exit("Mutex unlock failed\n");
}