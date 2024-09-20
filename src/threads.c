/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:57:46 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 22:37:43 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_lock(t_philosophers *philo, char *msg)
{
	
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d %s", timestamp_in_ms() - philo->data->start_time, philo->id_philo, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*philosopher_rutine(void *arg)
{
	t_philosophers *philo = (t_philosophers *) arg;
	
	if (philo->id_philo % 2 == 0)
		usleep(100);
	while (1)
	{
		
		pthread_mutex_lock(philo->left_fork);
		print_lock(philo, "has taken the left fork\n");
		
		pthread_mutex_lock(philo->right_fork);
		print_lock(philo, "has taken the right fork\n");
		
		
		print_lock(philo, "is eating\n");
		usleep(philo->data->time_to_eat * 1000);

		philo->meals_eaten++;
		
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		print_lock(philo, "is sleeping\n");
		usleep(philo->data->time_to_sleep * 1000);
		
		print_lock(philo, "is thinking\n");
	}
	return (NULL);
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
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	return (1);
}