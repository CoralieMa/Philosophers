/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:39 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/08 11:37:23 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define DEAD 0
# define SLEEP 1
# define EAT 2
# define THINK 3

typedef struct s_infos
{
	int					valid_infos;
	int					number_of_philosophers;
	int					number_of_times_each_philosopher_must_eat;
	long				last_time;
	long				begin_time;
	useconds_t			time_to_die;
	useconds_t			time_to_eat;
	useconds_t			time_to_sleep;
	pthread_mutex_t		*forks;
	pthread_mutex_t		msg;
}				t_infos;

typedef struct s_philo
{
	int		philo_nb;
	int		philo_status;
	t_infos	*infos;
}				t_philo;

int		ft_isdigit(char c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		error_msg(int type, char *msg, int i);
int		input_not_valid(int argc, char **argv);
int		ft_thread(t_philo *philo, int nb_philos);
long	get_time(t_infos *infos);
void	ft_msleep(int ms);
void	*routine(void *arg);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	get_time_beginning(t_infos *infos);
void	ft_pthread_mutex_init(t_infos *infos);
void	ft_pthread_mutex_destroy(t_infos *infos);
t_philo	*initialise_data(int argc, char **argv, t_infos *infos);

#endif
