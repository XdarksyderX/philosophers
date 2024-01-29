#include "philo.h"

void	sem_init(t_semaphore *sem, int count)
{
	if (count == 0)
		count = 1;
	pthread_mutex_init(&sem->mutex, NULL);
	sem->count = count;
}

void	sem_destroy(t_semaphore *sem)
{
	pthread_mutex_destroy(&sem->mutex);
}

void	sem_wait(t_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	while (sem->count <= 0)
	{
		pthread_mutex_unlock(&sem->mutex);
		usleep(1000);
		pthread_mutex_lock(&sem->mutex);
	}
	sem->count--;
	pthread_mutex_unlock(&sem->mutex);
}

void	sem_signal(t_semaphore *sem)
{
	pthread_mutex_lock(&sem->mutex);
	sem->count++;
	pthread_mutex_unlock(&sem->mutex);
}
