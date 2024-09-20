/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:57:46 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 17:18:29 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_rutine(void *arg)
{
	t_philosophers *philo = (t_philosophers *) arg;
	
	while (philo->meals_eaten < philo->data->must_eat_count)
	{
		printf("%lld %d is thinking", timestamp_in_ms() - philo->data->start_time, philo->id_philo);
		
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken the left fork\n", timestamp_in_ms() - philo->data->start_time, philo->id_philo);
		
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken the right fork\n", timestamp_in_ms() - philo->data->start_time, philo->id_philo);

		printf("%lld %d is eating\n", timestamp_in_ms() - philo->data->start_time, philo->id_philo);
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		printf("%lld %d is sleeping\n", timestamp_in_ms() - philo->data->start_time, philo->id_philo);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return;
}


int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].data = data;
		if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_rutine, &data->philosophers[i]) != 0)
			return(0);
		i++;
	}

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(&data->philosophers[i].thread, NULL);
		i++;
	}
	return (1);
}