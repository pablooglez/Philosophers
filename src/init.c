/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:44 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 14:51:51 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philosophers) * data->number_of_philosophers);
	if (!data->philosophers)
		return (0);

	int	i;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i].id_philo = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_eating = 0;

		data->philosophers[i].left_fork = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].right_fork = &data->forks[0];
		else
			data->philosophers[i].right_fork = &data->forks[i + 1];
		i++;
	}
	return (1);
}


int	init_simulation(t_data *data)
{	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (0);

	int	i;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}

	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return(0);

	if (!init_philosophers(&data));
		return (0);
	
	data->start_time = timestamp_in_ms();

	return (1);
}

