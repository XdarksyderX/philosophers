/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:24:38 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:35:18 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

int	ft_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_destroy(mutex);
	if (ret != 0)
		ft_error("Error destroying mutex");
	return (ret);
}

void	ft_clean_exit(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]->mutex);
		if (data->philosophers[i]->is_satiated == false
			&& !data->philosophers[i]->is_dead)
			pthread_mutex_destroy(&data->philosophers[i]->mutex_philosopher);
		free(data->forks[i]);
		free(data->philosophers[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_simulation);
	pthread_mutex_destroy(&data->mutex_output);
	free(data);
}

int	ft_usleep(useconds_t usec)
{
	int	ret;

	ret = usleep(usec);
	if (ret != 0)
		ft_error("Error sleeping");
	return (ret);
}
