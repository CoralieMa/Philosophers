/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:39 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/02 13:55:59 by cmartino         ###   ########.fr       */
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
	useconds_t			time_to_die;
	useconds_t			time_to_eat;
	useconds_t			time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					start_sec;
	int					start_msec;
	pthread_mutex_t		*forks;
}				t_infos;

typedef struct s_philo
{
	int		philo_nb;
	int		philo_status;
	t_infos	*infos;
}				t_philo;

int		ft_isdigit(char c);
int		get_time(t_infos *infos);
int		ft_atoi(const char *str);
int		error_msg(int type, char *msg, int i);
int		input_not_valid(int argc, char **argv);
int		ft_thread(t_philo *philo, int nb_philos);
void	*routine(void *arg);
void	get_time_beginning(t_infos *infos);
t_philo	*initialise_data(int argc, char **argv, t_infos *infos);

#endif
