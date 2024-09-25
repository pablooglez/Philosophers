/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:44 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/24 17:35:19 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_resources(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	pthread_mutex_destroy(&data->print_lock);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc
		(sizeof(t_philosophers) * data->number_of_philosophers);
	if (!data->philosophers)
	{
		free_resources(data);
		return (0);
	}
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id_philo = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_eating = timestamp_in_ms();
		data->philosophers[i].left_fork = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].right_fork = &data->forks[0];
		else
			data->philosophers[i].right_fork = &data->forks[i + 1];
		i++;
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc
		(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
	{
		free_resources(data);
		return (0);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free_resources(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_simulation(t_data *data)
{
	data->died_philosopher = 0;
	if (!init_forks(data))
		return (0);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
	{
		free_resources(data);
		return (0);
	}
	if (!init_philosophers(data))
	{
		free_resources(data);
		return (0);
	}
	data->start_time = timestamp_in_ms();
	return (1);
}
