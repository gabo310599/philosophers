/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:19:44 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:25:06 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//Validamos los valores
static int	validate_values(t_table *table)
{
	if (table->num_philos <= 0)
		return (1);
	if (table->time_to_die <= 0)
		return (1);
	if (table->time_to_eat <= 0)
		return (1);
	if (table->time_to_sleep <= 0)
		return (1);
	if (table->must_eat_flag && table->must_eat_count <= 0)
		return (1);
	return (0);
}

//Parseamos los argumentos introducidos
int	parse_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!ft_is_number(argv[1]) || !ft_is_number(argv[2])
		|| !ft_is_number(argv[3]) || !ft_is_number(argv[4])
		|| (argc == 6 && !ft_is_number(argv[5])))
		return (1);
	table->num_philos = ft_atol_safe(argv[1]);
	table->time_to_die = ft_atol_safe(argv[2]);
	table->time_to_eat = ft_atol_safe(argv[3]);
	table->time_to_sleep = ft_atol_safe(argv[4]);
	if (argc == 6)
	{
		table->must_eat_count = ft_atol_safe(argv[5]);
		table->must_eat_flag = true;
	}
	else
		table->must_eat_flag = false;
	if (validate_values(table))
		return (1);
	return (0);
}
