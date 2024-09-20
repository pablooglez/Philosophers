/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:04 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 15:08:33 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philosophers
{
	int				id_philo;
	int				meals_eaten;
	long long		last_meal_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}t_philosophers;


typedef struct s_data
{
	int				number_of_philosophers;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	t_philosophers	*philosophers;
}t_data;

#endif

//--------------------INIT---------------------//
int			init_philosophers(t_data *data);
int			init_simulation(t_data *data);

//--------------------PARSE--------------------//
int			parse_arguments(int argc, char *argv, t_data *data);

//--------------------UTILS--------------------//
int			ft_strlen(char *str);
long long	timestamp_in_ms(void);