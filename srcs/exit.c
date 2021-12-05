/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:22:06 by yun               #+#    #+#             */
/*   Updated: 2021/08/26 20:55:30 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	*exit_actions(int value)
{
	int	*ret;

	ret = NULL;
	if (value)
	{
		ret = malloc(sizeof(int));
		if (!ret)
		{
			write(1, "Error malloc\n", 13);
			return (ret);
		}
		*ret = 1;
		if (value == 1)
			write(1, "Error routines\n", 15);
		else if (value == 2)
			write(1, "Error check death\n", 18);
	}
	return (ret);
}

int	exit_philo(int ret, t_data *data)
{
	if (data->threads_philos)
		free(data->threads_philos);
	if (data->mutex_forks)
		free(data->mutex_forks);
	if (data->last_eat_time)
		free(data->last_eat_time);
	if (data->threads_deaths)
		free(data->threads_deaths);
	if (data->nb_meats)
		free(data->nb_meats);
	return (ret);
}

int	exit_disp(char *disp, int fd)
{
	int	i;

	i = 0;
	while (disp[i])
		i++;
	write(fd, disp, i);
	return (fd);
}
