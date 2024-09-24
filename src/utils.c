/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:34:43 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/24 19:30:55 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp_in_ms(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
	return (milliseconds);
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
		if (timestamp_in_ms()
			- philo->last_meal_eating > philo->data->time_to_die)
		{
			print_lock(philo, "died\n");
			philo->data->died_philosopher = 1;
			return (1);
		}
		usleep(100);
	}
	return (0);
}

int	print_lock(t_philosophers *philo, char *msg)
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
		pthread_mutex_lock(&philo->data->print_lock);
		printf("[%lld] %d %s",
			timestamp_in_ms() - philo->data->start_time,
			philo->id_philo, "died\n");
		philo->data->died_philosopher = 1;
		pthread_mutex_unlock(&philo->data->print_lock);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d %s ",
		timestamp_in_ms() - philo->data->start_time, philo->id_philo, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
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
