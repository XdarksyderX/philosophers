#include "philo.h"

void	ft_take_forks(t_philosopher *philosopher)
{
	sem_wait(&philosopher->shared_data->sem);
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
	sem_signal(&philosopher->shared_data->sem);
}

void	ft_sleep(t_philosopher *philosopher)
{
	if (philosopher->shared_data->is_simulation_ended)
		return ;
	ft_print_status(philosopher, "is sleeping\n");
	usleep(philosopher->shared_data->time_needed_to_sleep * 1000);
}

void	ft_think(t_philosopher *philosopher)
{
	ft_print_status(philosopher, "is thinking\n");
}
