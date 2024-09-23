/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:57:46 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/23 21:26:33 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		printf("[%lld] %d %s", timestamp_in_ms() - philo->data->start_time, philo->id_philo, "died\n");
		philo->data->died_philosopher = 1;
		pthread_mutex_unlock(&philo->data->print_lock);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_lock);
	
	printf("[%lld] %d %s", timestamp_in_ms() - philo->data->start_time, philo->id_philo, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

void	*philosopher_rutine(void *arg)
{
	t_philosophers *philo = (t_philosophers *) arg;
	
	if (philo->id_philo % 2 == 0)
		uwait(philo->data->time_to_eat, philo);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_lock(philo, "has taken the left fork\n");
	
		if (philo->data->number_of_philosophers == 1)
		{
			if (uwait(philo->data->time_to_die + 10, philo))
			{
				pthread_mutex_unlock(philo->left_fork);
				break;
			}
		}
		pthread_mutex_lock(philo->right_fork);
		if (print_lock(philo, "has taken the right fork\n"))
		{
			pthread_mutex_unlock(philo->left_fork);
			break;
		}
		
		print_lock(philo, "is eating\n");
		philo->last_meal_eating = timestamp_in_ms ();
		if (uwait(philo->data->time_to_eat, philo))
			break;

		philo->meals_eaten++;

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_lock(philo, "is sleeping\n");
		if(uwait(philo->data->time_to_sleep, philo))
			break;
		
		print_lock(philo, "is thinking\n");
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers_done = 0;
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