/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:26 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/04 11:18:24 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_thread(t_philo *philo, int nb_philos)
{
	pthread_t		*philo_thread;
	t_philo			*res;
	int				i;

	philo_thread = malloc(sizeof(pthread_t) * (size_t)nb_philos);
	if (!philo_thread)
		return (error_msg(4, "malloc error", 0));
	ft_pthread_mutex_init(philo[0].infos);
	i = 0;
	get_time_beginning(philo[0].infos);
	while (i < nb_philos)
	{
		if (pthread_create(&philo_thread[i], NULL, &routine, &(philo[i])) != 0)
			return (1);
		++i;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philo_thread[i], (void **)&res) != 0)
			return (1);
		philo[i] = *res;
		free(res);
		++i;
	}
	ft_pthread_mutex_destroy(philo[0].infos);
	free(philo_thread);
	return (0);
}
