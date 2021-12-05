/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:30:24 by yun               #+#    #+#             */
/*   Updated: 2021/08/26 21:02:37 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	unsigned int	nb_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nb_meats_value;
	unsigned int	*nb_meats;

	unsigned int	index;
	int				bool_nb_meats;
	int				philo_death;
	unsigned int	*last_eat_time;
	int				death;

	pthread_t		*threads_philos;
	pthread_t		*threads_deaths;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_disp;

	struct timeval	time;

}					t_data;

int				check_uint_limit(char *str);
unsigned int	ft_atoi(char *str);
int				exit_disp(char *disp, int fd);
unsigned int	get_time(struct timeval time);
int				exit_philo(int ret, t_data *data);
int				*exit_actions(int value);
void			*actions(void *param);
void			ft_usleep(unsigned int time, struct timeval tmp);
void			*check_death(void *params);
int				init_data(char **av, t_data *data, int ac);
int				malloc_data(t_data *data);
int				init_mutex(t_data *data);
void			disp_message(char *str, unsigned int n, unsigned int i);

#endif
