/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:26 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/26 11:03:23 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *philo, int i)
{
	philo->philo_nb = i + 1;
	philo->left_fork = 1;
	philo->right_fork = 1;
	philo->philo_status = 1;
}

int	ft_thread(t_infos *infos)
{
	pthread_t		*philo_thread;
	pthread_mutex_t	mutex;
	int				i;
	t_philo			*res;

	philo_thread = malloc(sizeof(pthread_t) * (size_t)infos->number_of_philosophers);
	if (!philo_thread)
		return (error_msg(4, "malloc error", 0));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_create(&philo_thread[i], NULL, &routine, &infos->philo[i]) != 0)
			return (1);
		++i;
	}
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_join(philo_thread[i], (void **) &res) != 0)
			return (1);
		(infos->philo[i]) = *res;
		free(res);
		++i;
	}
	pthread_mutex_destroy(&mutex);
	free(philo_thread);
	return (0);
}
