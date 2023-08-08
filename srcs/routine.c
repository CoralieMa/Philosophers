/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/08 11:34:39 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_msg(t_philo *philo, t_infos *infos, char *msg)
{
	pthread_mutex_lock(&(philo->infos->msg));
	printf("%ld ms %d %s", get_time(infos), philo->philo_nb + 1, msg);
	pthread_mutex_unlock(&(philo->infos->msg));
}

void	*routine(void *arg)
{
	t_philo	*result;
	t_philo	philos;

	philos = *(t_philo *)arg;
	result = malloc(sizeof(t_philo));
	if (philos.philo_nb % 2 != 0)
		ft_msleep(1);
	pthread_mutex_lock(&(philos.infos->forks[philos.philo_nb]));
	print_msg(&philos, philos.infos, " has taken a fork\n");
	if ((philos.infos->number_of_philosophers -1) != philos.philo_nb)
		pthread_mutex_lock(&(philos.infos->forks[philos.philo_nb + 1]));
	else
		pthread_mutex_lock(&(philos.infos->forks[0]));
	print_msg(&philos, philos.infos, " has taken a fork\n");
	print_msg(&philos, philos.infos, " is eating\n");
	ft_msleep(philos.infos->time_to_eat);
	pthread_mutex_unlock(&(philos.infos->forks[philos.philo_nb]));
	if ((philos.infos->number_of_philosophers -1) != philos.philo_nb)
		pthread_mutex_unlock(&(philos.infos->forks[philos.philo_nb + 1]));
	else
		pthread_mutex_unlock(&(philos.infos->forks[0]));
	print_msg(&philos, philos.infos, "is sleeping\n");
	*result = philos;
	return ((void *)result);
}
