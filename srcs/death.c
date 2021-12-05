/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:10:11 by yun               #+#    #+#             */
/*   Updated: 2021/08/26 21:08:30 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_disp_die(t_data *data, unsigned int tmp, unsigned int index_philo)
{
	if (pthread_mutex_lock(&data->mutex_disp))
		return (2);
	if (pthread_mutex_lock(&data->mutex_death))
		return (2);
	data->death++;
	if (data->death == 1 \
		&& ((data->bool_nb_meats && \
			data->nb_meats[index_philo] != 0) || data->bool_nb_meats == 0))
		printf("%u %u died\n", tmp, index_philo + 1);
	if (pthread_mutex_unlock(&data->mutex_disp))
		return (2);
	if (pthread_mutex_unlock(&data->mutex_death))
		return (2);
	return (0);
}

void	*check_death(void *params)
{
	t_data			*data;
	unsigned int	actual_time;
	unsigned int	index_philo;
	unsigned int	tmp;

	tmp = 0;
	data = (t_data *)params;
	index_philo = data->index;
	while (!data->death)
	{
		tmp = get_time(data->time);
		actual_time = tmp - data->last_eat_time[index_philo];
		if (actual_time >= data->time_to_die && !data->death)
		{
			if (philo_disp_die(data, tmp, index_philo))
				return ((void *)exit_actions(2));
		}
		usleep(10);
	}
	return ((void *)exit_actions(0));
}
