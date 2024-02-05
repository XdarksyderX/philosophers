/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:24:16 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:34:35 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_philosopher(void *philosopher)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philosopher;
	if (phil->id % 2 != 0)
		ft_usleep(10);
	while (!phil->shared_data->is_simulation_ended && !phil->is_satiated)
	{
		ft_take_forks(phil);
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil);
	}
	return (NULL);
}

static bool	ft_is_simulation_ended(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		if (data->philosophers[i]->is_satiated == false)
			return (false);
		i++;
	}
	return (true);
}

static void	*ft_monitor(void *data)
{
	t_simulation_data	*sim_data;
	int					i;

	sim_data = (t_simulation_data *)data;
	while (sim_data->is_simulation_ended == false)
	{
		i = 0;
		while (i < sim_data->total_philosophers)
		{
			pthread_mutex_lock(&sim_data->philosophers[i]->mutex_philosopher);
			if (ft_timestamp() - sim_data->philosophers[i]->last_meal_timestamp
				> sim_data->max_time_to_die || ft_is_simulation_ended(sim_data))
			{
				if (ft_is_simulation_ended(sim_data))
					return (NULL);
				ft_print_status(sim_data->philosophers[i], "died\n");
				sim_data->is_simulation_ended = true;
				return (sim_data->philosophers[i]->is_dead = true, NULL);
			}
			pthread_mutex_unlock(&sim_data->philosophers[i]->mutex_philosopher);
			i++;
		}
		ft_usleep(10);
	}
	return (NULL);
}

static void	ft_create_threads(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		if (i % 2 == 0)
		{
			pthread_create(&data->philosophers[i]->thread_id, NULL,
				ft_philosopher, data->philosophers[i]);
		}
		i++;
	}
	i = 0;
	while (i < data->total_philosophers)
	{
		if (i % 2 != 0)
		{
			pthread_create(&data->philosophers[i]->thread_id, NULL,
				ft_philosopher, data->philosophers[i]);
		}
		i++;
	}
	pthread_create(&data->thread_monitor, NULL, ft_monitor, data);
}

void	ft_start_simulation(t_simulation_data *data)
{
	int	i;

	ft_create_threads(data);
	i = 0;
	while (i < data->total_philosophers)
	{
		ft_pthread_join(data->philosophers[i]->thread_id, NULL);
		i++;
	}
	ft_pthread_join(data->thread_monitor, NULL);
}
