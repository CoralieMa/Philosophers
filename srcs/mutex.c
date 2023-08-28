/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:01:45 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/28 10:51:12 by cmartino         ###   ########.fr       */
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
	if (pthread_mutex_destroy(&infos->check_last_meal) != 0)
	{
		infos->infos_ft = -8;
		printf("Error in mutex destruction last_meal\n");
	}
	if (pthread_mutex_destroy(&infos->msg) != 0)
	{
		infos->infos_ft = -8;
		printf("Error in mutex destruction msg\n");
	}
	while (i < infos->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&infos->forks[i]) != 0)
		{
			infos->infos_ft = -8;
			printf("Error in mutex destruction fork %d\n", i);
		}
		++i;
	}
}

static int	ft_error_mutex_init(t_infos *infos, int i)
{
	int	j;

	j = 0;
	infos->infos_ft = -8;
	infos->valid_infos = 1;
	printf("Error in mutex initialisation\n");
	if (i > -2)
	{
		if (pthread_mutex_destroy(&infos->check_last_meal) != 0)
			printf("Error in mutex destruction last_meal\n");
	}
	if (i > -1)
	{
		if (pthread_mutex_destroy(&infos->msg) != 0)
			printf("Error in mutex destruction msg\n");
		while (j < i)
		{
			if (pthread_mutex_destroy(&infos->forks[i]) != 0)
				printf("Error in mutex destruction forks\n");
			++j;
		}
	}
	return (-1);
}

int	ft_pthread_mutex_init(t_infos *infos)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = pthread_mutex_init(&infos->check_last_meal, NULL);
	if (return_value != 0)
		return (ft_error_mutex_init(infos, -2));
	return_value = pthread_mutex_init(&infos->msg, NULL);
	if (return_value != 0)
		return (ft_error_mutex_init(infos, -1));
	while (i < infos->number_of_philosophers)
	{
		return_value = pthread_mutex_init(&infos->forks[i], NULL);
		if (return_value != 0)
			return (ft_error_mutex_init(infos, i));
		++i;
	}
	return (0);
}
