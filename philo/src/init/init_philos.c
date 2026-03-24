/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:36:37 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/24 21:18:04 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Asignamos los tenedores
static void	assign_forks(t_philo *philo, t_table *table, int i)
{
	if (i == table->num_philos - 1)
	{
		philo->left_fork = &table->forks[0];
		philo->right_fork = &table->forks[i];
	}
	else
	{
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[i + 1];
	}
}

//Inicializamos a los philos
int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].table = table;
		assign_forks(&table->philos[i], table, i);
		i++;
	}
	return (0);
}
