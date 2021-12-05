/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:02:20 by yun               #+#    #+#             */
/*   Updated: 2021/09/22 14:42:04 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_take_fork(t_data *data, unsigned int index_philo, unsigned int fork)
{
	unsigned int	ms;

	ms = 0;
	if (pthread_mutex_lock(&data->mutex_forks[fork]))
		return (1);
	if (pthread_mutex_lock(&data->mutex_disp))
		return (1);
	ms = get_time(data->time);
	if (!data->death)
		printf("%u %u has taken a fork\n", ms, index_philo + 1);
	if (pthread_mutex_unlock(&data->mutex_disp))
		return (1);
	return (0);
}

int	philo_eat(t_data *data, unsigned int index_philo, unsigned int r)
{
	if (philo_take_fork(data, index_philo, index_philo))
		return (1);
	if (pthread_mutex_lock(&data->mutex_disp))
		return (1);
	data->last_eat_time[index_philo] = get_time(data->time);
	if (!data->death)
		printf("%u %u is eating\n", \
			data->last_eat_time[index_philo], index_philo + 1);
	if (pthread_mutex_unlock(&data->mutex_disp))
		return (1);
	ft_usleep(data->time_to_eat * 1000, data->time);
	if (pthread_mutex_unlock(&data->mutex_forks[r]))
		return (1);
	if (pthread_mutex_unlock(&data->mutex_forks[index_philo]))
		return (1);
	return (0);
}

int	philo_sleep(t_data *data, unsigned int index_philo)
{
	unsigned int	ms;

	ms = 0;
	if (pthread_mutex_lock(&data->mutex_disp))
		return (1);
	ms = get_time(data->time);
	if (!data->death)
		printf("%u %u is sleeping\n", ms, index_philo + 1);
	if (pthread_mutex_unlock(&data->mutex_disp))
		return (1);
	ft_usleep(data->time_to_sleep * 1000, data->time);
	if (pthread_mutex_lock(&data->mutex_disp))
		return (1);
	ms = get_time(data->time);
	if (!data->death)
		printf("%u %u is thinking\n", ms, index_philo + 1);
	if (pthread_mutex_unlock(&data->mutex_disp))
		return (1);
	return (0);
}

void	*actions(void *params)
{
	t_data			*data;
	unsigned int	index_philo;
	unsigned int	r;

	data = (t_data *)params;
	index_philo = data->index;
	r = index_philo - 1;
	if (index_philo == 0)
		r = data->nb_philos - 1;
	while (!data->death && ((data->bool_nb_meats && \
		data->nb_meats[index_philo]) || data->bool_nb_meats == 0))
	{
		if (philo_take_fork(data, index_philo, r))
			return ((void *)exit_actions(1));
		if (data->nb_philos == 1)
			return ((void *)exit_actions \
				(pthread_mutex_unlock(&data->mutex_forks[r])));
		if (philo_eat(data, index_philo, r) || philo_sleep(data, index_philo))
			return ((void *)exit_actions(1));
		if (data->bool_nb_meats)
			data->nb_meats[index_philo] -= 1;
	}
	return ((void *)exit_actions(0));
}
