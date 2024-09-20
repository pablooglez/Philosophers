/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:34:22 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 22:02:57 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_simulation(t_data *data)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->print_lock);
			
			if (timestamp_in_ms() - data->philosophers[i].last_meal_eating > data->time_to_die)
			{
				printf("%lld %d philosopher died\n", timestamp_in_ms() - data->start_time, data->philosophers[i].id_philo);
				pthread_mutex_unlock(&data->print_lock);
				return;
			}
			pthread_mutex_unlock(&data->print_lock);
			i++;
		}
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (data->must_eat_count == -1 && data->philosophers[i].meals_eaten < data->must_eat_count)
				break;
			i++;
		}
		usleep(1000);
	}
}