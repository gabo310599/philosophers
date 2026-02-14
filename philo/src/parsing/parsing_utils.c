/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:philo/src/parser.c
/*   Created: 2025/07/31 11:46:35 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/07 20:28:42 by gojeda           ###   ########.fr       */
=======
/*   Created: 2026/02/14 12:20:02 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 12:31:46 by gojeda           ###   ########.fr       */
>>>>>>> c4889b8 (philos2.0 (new version, needs testing and readme)):philo/src/parsing/parsing_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

//Verificamos que un string sea un numero
int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

//Atol para parseo seguro
long	ft_atol_safe(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
<<<<<<< HEAD:philo/src/parser.c
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		rules->must_eat_count = ft_atoi(argv[5]);
		if (rules->must_eat_count <= 0)
			return ((print_error("must_eat_count debe ser > 0"), 0));
	}
	else
		rules->must_eat_count = -1;
	return (rules->someone_died = 0, rules->start_time = get_time_in_ms(), 1);
=======
	return (result);
>>>>>>> c4889b8 (philos2.0 (new version, needs testing and readme)):philo/src/parsing/parsing_utils.c
}
