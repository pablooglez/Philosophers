/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:34:43 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/20 18:24:26 by pablogon         ###   ########.fr       */
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