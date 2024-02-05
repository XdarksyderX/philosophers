/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:23:59 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:24:11 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation_data	*data;

	if (argc < 5 || argc > 6)
		ft_error("Wrong number of arguments");
	data = ft_init_data(argc, argv);
	ft_start_simulation(data);
	ft_clean_exit(data);
	return (0);
}
