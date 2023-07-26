/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:39 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/26 11:00:31 by cmartino         ###   ########.fr       */
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

# define DEAD 0
# define SLEEP 1
# define EAT 2
# define THINK 3

typedef struct s_philo
{
	int	philo_nb;
	int	philo_status;
	int	left_fork;
	int	right_fork;
}				t_philo;

typedef struct s_infos
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int		valid_infos;
	t_philo	*philo;
}				t_infos;

int		ft_isdigit(char c);
int		ft_atoi(const char *str);
int		ft_thread(t_infos *infos);
int		initialise_philo(t_infos *infos);
int		error_msg(int type, char *msg, int i);
int		input_not_valid(int argc, char **argv);
void	*routine(void *arg);
t_infos	initialise_data(int argc, char **argv);

#endif
