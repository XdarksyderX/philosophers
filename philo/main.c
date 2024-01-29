#include "philo.h"

void	ft_debug(t_simulation_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{
		printf("Philosopher %d:\n", i);
		printf("id: %d\n", data->philosophers[i]->id);
		printf("meals_eaten_count: %d\n", data->philosophers[i]->meals_eaten_count);
		printf("last_meal_timestamp: %i\n", data->philosophers[i]->last_meal_timestamp);
		printf("left_fork: %d\n", data->philosophers[i]->left_fork->fork_id);
		printf("right_fork: %d\n", data->philosophers[i]->right_fork->fork_id);
		printf("is_satiated: %d\n", data->philosophers[i]->is_satiated);
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation_data	*data;

	if (argc < 5 || argc > 6)
		ft_error("Wrong number of arguments");
	data = ft_init_data(argc, argv);
	ft_start_simulation(data);
	//ft_debug(data);
	return (0);
}
