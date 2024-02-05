/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:24:29 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:24:30 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philosopher *philosopher)
{
	if (philosopher->shared_data->is_simulation_ended)
		return ;
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->left_fork->mutex);
		ft_print_status(philosopher, "has taken a fork\n");
		pthread_mutex_lock(&philosopher->right_fork->mutex);
		ft_print_status(philosopher, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philosopher->right_fork->mutex);
		ft_print_status(philosopher, "has taken a fork\n");
		pthread_mutex_lock(&philosopher->left_fork->mutex);
		ft_print_status(philosopher, "has taken a fork\n");
	}
}

void	ft_eat(t_philosopher *philosopher)
{
	if (philosopher->shared_data->is_simulation_ended)
		return ;
	pthread_mutex_lock(&philosopher->mutex_philosopher);
	ft_print_status(philosopher, "is eating\n");
	philosopher->last_meal_timestamp = ft_timestamp();
	philosopher->meals_eaten_count++;
	pthread_mutex_unlock(&philosopher->mutex_philosopher);
	usleep(philosopher->shared_data->time_needed_to_eat * 1000);
	pthread_mutex_unlock(&philosopher->left_fork->mutex);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
	if (philosopher->shared_data->max_meals_per_philosopher > 0
		&& philosopher->meals_eaten_count
		== philosopher->shared_data->max_meals_per_philosopher)
		philosopher->is_satiated = true;
}

void	ft_sleep(t_philosopher *philosopher)
{
	if (philosopher->shared_data->is_simulation_ended)
		return ;
	ft_print_status(philosopher, "is sleeping\n");
	ft_usleep(philosopher->shared_data->time_needed_to_sleep * 1000);
}

void	ft_think(t_philosopher *philosopher)
{
	int	time_to_think;

	ft_print_status(philosopher, "is thinking\n");
	if (philosopher->shared_data->total_philosophers % 2 == 0)
		return ;
	time_to_think = (philosopher->shared_data->time_needed_to_eat
			+ philosopher->shared_data->time_needed_to_sleep) / 2;
	if (time_to_think < 1)
		return ;
	ft_usleep(time_to_think * 1000);
}
