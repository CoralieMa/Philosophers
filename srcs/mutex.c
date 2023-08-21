/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:01:45 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/21 13:02:59 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_unlock(&infos->forks[i]);
		++i;
	}
}

void	ft_pthread_mutex_destroy(t_infos *infos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&infos->msg);
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		++i;
	}
}

void	ft_pthread_mutex_init(t_infos *infos)
{
	int	i;

	i = 0;
	pthread_mutex_init(&infos->msg, NULL);
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_init(&infos->forks[i], NULL);
		++i;
	}
}
