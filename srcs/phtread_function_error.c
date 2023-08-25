/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phtread_function_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:43:39 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 11:39:33 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pthread_join_error(t_infos *infos, int i)
{
	infos->valid_infos = 1;
	infos->infos_ft = -8;
	pthread_mutex_lock(&(infos->msg));
	printf("pthread_join() philo n. %d failed\n", i);
	pthread_mutex_unlock(&(infos->msg));
}

int	pthread_create_error(t_philo *philo, pthread_t *philo_th, int i)
{
	int	j;

	j = 0;
	philo[0].infos->valid_infos = 1;
	philo[0].infos->infos_ft = -8;
	pthread_mutex_lock(&(philo[0].infos->msg));
	printf("pthread_create() philo n. %d failed\n", i);
	pthread_mutex_unlock(&(philo[0].infos->msg));
	while (j < i)
	{
		if (pthread_join(philo_th[i], NULL) != 0)
			pthread_join_error(philo[0].infos, i + 1);
		++j;
	}
	return (1);
}
