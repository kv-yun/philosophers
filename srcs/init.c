/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 17:31:37 by yun               #+#    #+#             */
/*   Updated: 2021/09/22 14:38:55 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(char **av, t_data *data, int ac)
{
	int	i;

	i = 0;
	while (av[++i])
		if (check_uint_limit(av[i]))
			return (1);
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->bool_nb_meats = 0;
	data->nb_meats = NULL;
	if (ac == 6)
	{
		data->nb_meats_value = ft_atoi(av[5]);
		data->bool_nb_meats = 1;
	}
	data->death = 0;
	return (0);
}

int	init_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->bool_nb_meats == 1)
			data->nb_meats[i] = data->nb_meats_value;
		if (pthread_mutex_init(&data->mutex_forks[i], NULL))
			return (exit_disp("Error init mutex\n", 1));
		i++;
	}
	if (pthread_mutex_init(&data->mutex_death, NULL))
		return (exit_disp("Error init mutex\n", 1));
	if (pthread_mutex_init(&data->mutex_disp, NULL))
		return (exit_disp("Error init mutex\n", 1));
	return (0);
}

int	malloc_data(t_data *data)
{
	data->threads_philos = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->threads_philos)
		return (exit_disp("Error malloc\n", 1));
	data->threads_deaths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->threads_deaths)
		return (exit_disp("Error malloc\n", 1));
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->mutex_forks)
		return (exit_disp("Error malloc\n", 1));
	data->last_eat_time = malloc(sizeof(unsigned int) * data->nb_philos);
	if (!data->last_eat_time)
		return (exit_disp("Error malloc\n", 1));
	data->nb_meats = malloc(sizeof(unsigned int) * data->nb_philos);
	if (!data->nb_meats)
		return (exit_disp("Error malloc\n", 1));
	return (0);
}
