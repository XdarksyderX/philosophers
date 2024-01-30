#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>

//Times are in ms

typedef struct s_simulation_data	t_simulation_data;

typedef struct s_dining_fork
{
	pthread_mutex_t	mutex;
	int	fork_id;

}				t_dining_fork;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten_count;
	int					last_meal_timestamp;
	t_dining_fork		*left_fork;
	t_dining_fork		*right_fork;
	pthread_t			thread_id;
	pthread_mutex_t		mutex_philosopher;
	t_simulation_data	*shared_data;
	bool				is_satiated;

}	t_philosopher;

typedef struct s_simulation_data
{
	int				total_philosophers;
	int				max_time_to_die;
	int				time_needed_to_eat;
	int				time_needed_to_sleep;
	int				simulation_start_time;
	int				active_threads_count;
	int				max_meals_per_philosopher;
	t_dining_fork	**forks;
	t_philosopher	**philosophers;
	pthread_mutex_t	mutex_simulation;
	pthread_mutex_t	mutex_output;
	pthread_t		thread_monitor;
	bool			is_simulation_ended;

}	t_simulation_data;

//Utils
int		ft_timestamp(void);
int		ft_atou(const char *str);
void				ft_print_status(t_philosopher *phil, char *status);

//Management
void				ft_error(char *message);

//Actions
void	ft_take_forks(t_philosopher *philosopher);
void	ft_eat(t_philosopher *philosopher);
void	ft_think(t_philosopher *philosopher);
void	ft_sleep(t_philosopher *philosopher);

t_simulation_data	*ft_init_data(int argc, char **argv);
void	ft_start_simulation(t_simulation_data *data);

void	ft_clean_exit(t_simulation_data *data);

#endif