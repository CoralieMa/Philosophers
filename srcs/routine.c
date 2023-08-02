/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/02 10:09:56 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*result;
	t_philo	philos;

	philos = *(t_philo *)arg;
	result = malloc(sizeof(t_philo));
	if (philos.philo_nb % 2 != 0)
	{
		printf("Philo n. -> %d is sleeping\n\n", philos.philo_nb);
		usleep(3000);
	}
	pthread_mutex_lock(&(philos.infos->forks[philos.philo_nb]));
	if ((philos.infos->number_of_philosophers -1) != philos.philo_nb)
		pthread_mutex_lock(&(philos.infos->forks[philos.philo_nb]));
	else
		pthread_mutex_lock(&(philos.infos->forks[0]));
	printf("Hello philo n. -> %d gnom gnom gnom\n\n", philos.philo_nb);
	usleep(100);
	pthread_mutex_unlock(&(philos.infos->forks[philos.philo_nb - 1]));
	if ((philos.infos->number_of_philosophers -1) != philos.philo_nb)
		pthread_mutex_unlock(&(philos.infos->forks[philos.philo_nb]));
	else
		pthread_mutex_unlock(&(philos.infos->forks[0]));
	*result = philos;
	return ((void *)result);
}
