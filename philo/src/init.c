/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:24:34 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:24:35 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_dining_fork	*ft_create_fork(int id)
{
	t_dining_fork	*fork;

	fork = malloc(sizeof(t_dining_fork));
	if (!fork)
		ft_error("Malloc error");
	fork->fork_id = id;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

static t_philosopher	*ft_create_philosopher(t_simulation_data *data, int id)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		ft_error("Malloc error");
	philosopher->id = id;
	philosopher->meals_eaten_count = 0;
	philosopher->last_meal_timestamp = ft_timestamp();
	philosopher->left_fork = data->forks[id];
	philosopher->right_fork = data->forks[(id + 1) % data->total_philosophers];
	pthread_mutex_init(&philosopher->mutex_philosopher, NULL);
	philosopher->shared_data = data;
	philosopher->is_satiated = false;
	philosopher->is_dead = false;
	return (philosopher);
}

static t_simulation_data	*ft_fill_data(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		data->forks[i] = ft_create_fork(i);
		i++;
	}
	i = 0;
	while (i < data->total_philosophers)
	{
		data->philosophers[i] = ft_create_philosopher(data, i);
		i++;
	}
	pthread_mutex_init(&data->mutex_simulation, NULL);
	pthread_mutex_init(&data->mutex_output, NULL);
	return (data);
}

t_simulation_data	*ft_init_data(int argc, char **argv)
{
	t_simulation_data	*data;

	data = malloc(sizeof(t_simulation_data));
	if (!data)
		ft_error("Malloc error");
	data->total_philosophers = ft_atou(argv[1]);
	data->max_time_to_die = ft_atou(argv[2]);
	data->time_needed_to_eat = ft_atou(argv[3]);
	data->time_needed_to_sleep = ft_atou(argv[4]);
	data->max_meals_per_philosopher = -1;
	if (argc == 6)
		data->max_meals_per_philosopher = (int) ft_atou(argv[5]);
	data->simulation_start_time = ft_timestamp();
	data->is_simulation_ended = false;
	data->forks = malloc(sizeof(t_dining_fork *) * data->total_philosophers);
	if (!data->forks)
		ft_error("Malloc error");
	data->philosophers = malloc(sizeof(t_philosopher *)
			* data->total_philosophers);
	if (!data->philosophers)
		ft_error("Malloc error");
	data->active_threads_count = 0;
	return (ft_fill_data(data));
}
