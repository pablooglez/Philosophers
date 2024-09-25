/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:57:46 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/25 20:07:20 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philosophers *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_lock(philo, "has taken the left fork\n"))
		return (1);
	if (philo->data->number_of_philosophers == 1)
	{
		if (uwait(philo->data->time_to_die + 10, philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_lock(philo, "has taken the right fork\n"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	eat(t_philosophers *philo)
{
	if (print_lock(philo, "is eating\n"))
		return (1);
	philo->last_meal_eating = timestamp_in_ms ();
	if (uwait(philo->data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	philo->meals_eaten++;
	if (print_lock(philo, "is sleeping\n"))
		return (1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	sleep_and_think(t_philosophers *philo)
{
	if (uwait(philo->data->time_to_sleep, philo))
		return (1);
	if (print_lock(philo, "is thinking\n"))
		return (1);
	return (0);
}

void	*philosopher_rutine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *) arg;
	if (philo->id_philo % 2 == 0)
		uwait(philo->data->time_to_eat, philo);
	while (1)
	{
		if (take_forks(philo))
			break ;
		if (eat(philo))
			break ;
		if (philo->data->must_eat_count > 0
			&& all_philosophers_ate_enough(philo->data))
			break ;
		if (sleep_and_think(philo))
			break ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_rutine, &data->philosophers[i]) != 0)
			return (0);
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
