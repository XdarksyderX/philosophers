
#include "philo.h"

int	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print_status(t_philosopher *phil, char *status)
{
	pthread_mutex_lock(&phil->shared_data->mutex_output);
	if (phil->shared_data->is_simulation_ended)
	{
		pthread_mutex_unlock(&phil->shared_data->mutex_output);
		return ;
	}
	printf("[%d ms] Philosopher %d %s", ft_timestamp()
		-phil->shared_data->simulation_start_time, phil->id + 1, status);
	pthread_mutex_unlock(&phil->shared_data->mutex_output);
}

int	ft_atou(const char *str)
{
	unsigned int	result;
	int				sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		ft_error("Invalid argument: negative number");
	if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		ft_error("Invalid argument: not a number");
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			ft_error("Invalid argument: number is too big");
		str++;
	}
	return (result * sign);
}
