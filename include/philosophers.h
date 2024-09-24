/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:04 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/24 20:10:37 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philosophers
{
	int				id_philo;
	int				meals_eaten;
	long long		last_meal_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philosophers;

typedef struct s_data
{
	int				number_of_philosophers;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	int				died_philosopher;
	int				philosophers_done;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	t_philosophers	*philosophers;
}	t_data;

//--------------------INIT---------------------//
void		free_resources(t_data *data);
int			init_philosophers(t_data *data);
int			init_forks(t_data *data);
int			init_simulation(t_data *data);

//--------------------MONITOR------------------//
void		monitor_simulation(t_data *data);

//--------------------PARSE--------------------//
int			parse_arguments(int argc, char **argv, t_data *data);

//--------------------THREADS------------------//
int			take_forks(t_philosophers *philo);
int			eat(t_philosophers *philo);
int			sleep_and_think(t_philosophers *philo);
void		*philosopher_rutine(void *arg);
int			create_threads(t_data *data);

//--------------------UTILS--------------------//
long long	timestamp_in_ms(void);
int			uwait(long long time, t_philosophers *philo);
int			print_lock(t_philosophers *philo, char *msg);
int			all_philosophers_ate_enough(t_data *data);

//-------------------UTILS2--------------------//
int			ft_strlen(char *str);
int			ft_atoi(const char *str);
void		cleanup(t_data *data);

#endif