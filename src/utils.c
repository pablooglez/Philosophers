/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:34:43 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/23 18:13:42 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

#include <limits.h>

int ft_atoi(const char *str)
{
	long long num = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r') 
		i++;

	if (str[i] == '-' || str[i] == '+') 
	{
		if (str[i] == '-') 
			sign = -1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9') 
	{
		num = num * 10 + (str[i] - '0'); 
		i++;
		if (num * sign > INT_MAX) 
			return INT_MAX;
		if (num * sign < INT_MIN) 
			return INT_MIN;
	}
	return (int)(num * sign);
}

long long	timestamp_in_ms(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	
	milliseconds = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);

	return(milliseconds);
}

int	uwait(long long time, t_philosophers *philo)
{
	long long	start;
	
	start = timestamp_in_ms();

	while (timestamp_in_ms() - start < time)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo->data->died_philosopher == 1)
		{
			pthread_mutex_unlock(&philo->data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		if (timestamp_in_ms() - philo->last_meal_eating > philo->data->time_to_die)
		{
			print_lock(philo, "died\n");
			philo->data->died_philosopher = 1;
			return (1);
		}
		usleep(100);
	}
	return (0);
}

int	all_philosophers_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philosophers[i].meals_eaten < data->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}