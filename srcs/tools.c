/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:16:29 by yun               #+#    #+#             */
/*   Updated: 2021/08/28 13:06:25 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned int time, struct timeval tmp)
{
	unsigned int	start;
	unsigned int	real_time;

	start = get_time(tmp) * 1000;
	real_time = start;
	while (real_time < time + start)
	{
		usleep(50);
		real_time = get_time(tmp) * 1000;
	}
}

int	check_uint_limit(char *str)
{
	long long int	x;
	int				i;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (i > 10 || str[i] < '0' || str[i] > '9')
			return (1);
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (x > 4294967295)
		return (1);
	return (0);
}

unsigned int	ft_atoi(char *str)
{
	unsigned int	ret;
	int				i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	return (ret);
}

unsigned int	get_time(struct timeval time)
{
	unsigned int	ms;
	struct timeval	tmp;

	ms = 0;
	gettimeofday(&tmp, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ms = tmp.tv_sec * 1000 + tmp.tv_usec / 1000 - ms;
	return (ms);
}
