/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:24:43 by migarci2          #+#    #+#             */
/*   Updated: 2024/01/31 13:32:06 by migarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_create(pthread_t *thread_id, pthread_attr_t *attr,
	void *(*start_routine)(void *), void *arg)
{
	int	ret;

	ret = pthread_create(thread_id, attr, start_routine, arg);
	if (ret != 0)
		ft_error("Error creating thread");
	return (ret);
}

int	ft_pthread_join(pthread_t thread_id, void **retval)
{
	int	ret;

	ret = pthread_join(thread_id, retval);
	if (ret != 0)
		ft_error("Error joining thread");
	return (ret);
}

int	ft_pthread_mutex_init(pthread_mutex_t *mutex,
	const pthread_mutexattr_t *attr)
{
	int	ret;

	ret = pthread_mutex_init(mutex, attr);
	if (ret != 0)
		ft_error("Error initializing mutex");
	return (ret);
}
