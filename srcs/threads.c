/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:26 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/09 10:25:19 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_thread(t_philo *philo, int nb_philos, pthread_t *philo_thread)
{
	int	i;	

	i = 0;
	while (i < nb_philos)
	{
		philo[i].time_last_meal = philo[0].infos->begin_time;
		if (pthread_create(&philo_thread[i], NULL, &routine, &(philo[i])) != 0)
			return (1);
		++i;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philo_thread[i], NULL) != 0)
			return (1);
		++i;
	}
	return (0);
}

int	ft_thread(t_philo *philo, int nb_philos)
{
	pthread_t		*philo_thread;

	philo_thread = malloc(sizeof(pthread_t) * (size_t)nb_philos);
	if (!philo_thread)
		return (error_msg(4, "malloc error", 0));
	ft_pthread_mutex_init(philo[0].infos);
	get_time_beginning(philo[0].infos);
	init_thread(philo, nb_philos, philo_thread);
	ft_pthread_mutex_destroy(philo[0].infos);
	free(philo_thread);
	return (0);
}
