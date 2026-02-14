/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:24:23 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:45:26 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_args(argc, argv, &table))
		return (error_exit("Invalid arguments\n"));
	if (init_table(&table))
		return (error_exit("Mutex init failed\n"));
	if (init_forks(&table))
		return (error_exit("Forks init failed\n"));
	if (init_philos(&table))
		return (error_exit("Philos init failed\n"));
	if (create_threads(&table))
		return (error_exit("Thread creation failed\n"));
	join_threads(&table);
	cleanup(&table);
	return (0);
}
