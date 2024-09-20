/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:34:43 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 15:18:00 by pablogon         ###   ########.fr       */
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

long long	timestamp_in_ms(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	
	milliseconds = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);

	return(milliseconds);
}