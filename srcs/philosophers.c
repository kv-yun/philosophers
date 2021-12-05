/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:16:02 by yun               #+#    #+#             */
/*   Updated: 2021/09/07 19:08:35 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->index = i;
		data->last_eat_time[i] = 0;
		if (pthread_create(&(data->threads_philos[i]), \
			NULL, actions, (void *)data))
			return (exit_disp("Error creare philo threads\n", 1));
		if (pthread_create(&(data->threads_deaths[i]), \
			NULL, check_death, (void *)data))
			return (exit_disp("Error create death threads\n", 1));
		i++;
		usleep(100);
	}
	return (0);
}

int	return_retval(int *retval)
{
	int	ret;

	ret = 0;
	if (retval && *retval)
	{
		ret = *retval;
		free(retval);
	}
	return (ret);
}

int	philo_end(t_data *data)
{
	unsigned int	i;
	int				*retval;
	int				ret;

	ret = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->threads_philos[i], (void *)&retval))
			return (exit_philo(exit_disp("Error pthreads join\n", 1), data));
		ret = return_retval(retval);
		if (pthread_join(data->threads_deaths[i], (void *)&retval))
			return (exit_philo(exit_disp("Error pthreads join\n", 1), data));
		ret = return_retval(retval);
		i++;
	}
	return (exit_philo(ret, data));
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || init_data(av, &data, ac) \
		|| data.nb_philos == 0)
		return (exit_disp("Invalid argument\n", 1));
	if (malloc_data(&data) \
		|| gettimeofday(&data.time, NULL) || init_mutex(&data))
		return (exit_philo(1, &data));
	if (create_philos(&data))
		return (exit_philo(1, &data));
	while (!data.death)
		usleep(10);
	if (philo_end(&data))
		return (1);
	return (0);
}
