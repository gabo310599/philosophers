/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:07:13 by gojeda            #+#    #+#             */
/*   Updated: 2026/02/14 13:44:48 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

/* ANSI COLORS */
# define C_FORK   "\033[33m"
# define C_EAT    "\033[32m"
# define C_SLEEP  "\033[34m"
# define C_THINK  "\033[35m"
# define C_DIE    "\033[31m"
# define C_RESET  "\033[0m"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				must_eat_flag;
	long			start_time;
	bool			someone_died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
	t_philo			*philos;
}	t_table;

/* Parsing */
int		parse_args(int argc, char **argv, t_table *table);
int		ft_is_number(char *str);
long	ft_atol_safe(const char *str);

/* Init */
int		init_table(t_table *table);
int		init_forks(t_table *table);
int		init_philos(t_table *table);

/* Threads */
int		create_threads(t_table *table);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	join_threads(t_table *table);
void	safe_mutex_lock(pthread_mutex_t *mutex);
void	safe_mutex_unlock(pthread_mutex_t *mutex);

/* Actions */
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

/* Time */
long	get_time_ms(void);
long	timestamp(t_table *table);
void	precise_sleep(long time, t_table *table);

/* Print */
void	print_state(t_philo *philo, t_state state);

/* Stop */
int		simulation_stopped(t_table *table);
void	set_death(t_table *table);

/* Cleanup */
void	cleanup(t_table *table);
int		error_exit(char *msg);

#endif