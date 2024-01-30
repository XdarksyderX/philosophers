#include "philo.h"

void	ft_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

void	ft_clean_exit(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]->mutex);
		pthread_mutex_destroy(&data->philosophers[i]->mutex_philosopher);
		free(data->forks[i]);
		free(data->philosophers[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_simulation);
	pthread_mutex_destroy(&data->mutex_output);
	free(data);
}
