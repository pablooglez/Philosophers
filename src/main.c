/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:22:30 by pablogon          #+#    #+#             */
/*   Updated: 2024/09/09 22:57:17 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!parse_arguments(argc, argv, &data))
			return(write(2, "Error: The rules are wrong\n", 27), 1);
		if (!init_simulation(&data))
			return(write(2,"Error: Can't start simulation\n", 29), 1);
		if (!create_threads(&data))
			return(write(2,"Error: Can't create philosopher\n", 32), 1);
		monitor_simulation(&data);
		cleanup_simulation(&data);
	}
	else
		ft_error("Error: Incorrect arguments");
	return (0);
}