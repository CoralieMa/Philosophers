/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:01:45 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 14:46:26 by cmartino         ###   ########.fr       */
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

int	ft_pthread_mutex_destroy(t_infos *infos)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = pthread_mutex_destroy(&infos->check_last_meal);
	if (return_value != 0)
		printf("Error in mutex destruction 1\n");
	return_value = pthread_mutex_destroy(&infos->msg);
	if (return_value != 0)
		printf("Error in mutex destruction 2\n");
	while (i < infos->number_of_philosophers)
	{
		return_value = pthread_mutex_destroy(&infos->forks[i]);
		if (return_value != 0)
			printf("Error in mutex destruction 3\n");
		++i;
	}
	if (return_value != 0)
		infos->infos_ft = -8;
	return (return_value);
}

static int	ft_error_mutex_init(t_infos *infos)
{
	printf("Error in initializing mutex\n");
	infos->infos_ft = -8;
	infos->valid_infos = 1;
	return (-1);
}

int	ft_pthread_mutex_init(t_infos *infos)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = pthread_mutex_init(&infos->check_last_meal, NULL);
	if (return_value != 0)
		return (ft_error_mutex_init(infos));
	return_value = pthread_mutex_init(&infos->msg, NULL);
	if (return_value != 0)
		return (ft_error_mutex_init(infos));
	while (i < infos->number_of_philosophers)
	{
		return_value = pthread_mutex_init(&infos->forks[i], NULL);
		if (return_value != 0)
		{
			printf("Error in initializing mutex\n");
			infos->valid_infos = 1;
			infos->infos_ft = -8;
			return (return_value);
		}
		++i;
	}
	return (0);
}
