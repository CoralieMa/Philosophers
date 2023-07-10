/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:26 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/10 14:53:49 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function()
{
	printf("Hello from thread\n");
	return (NULL);
}

int	ft_thread(t_infos *infos)
{
	pthread_t		*philo_thread;
	pthread_mutex_t	mutex;
	int				i;

	philo_thread = malloc(sizeof(pthread_t) * (size_t)infos->number_of_philosophers);
	if (!philo_thread)
		return (error_msg(4, "malloc error", 0));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_create(&philo_thread[i], NULL, &thread_function, NULL) != 0)
			return (1);
		++i;
	}
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_join(philo_thread[i], NULL) != 0)
			return (1);
		++i;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
