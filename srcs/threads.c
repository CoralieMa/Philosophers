/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:53:26 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 16:30:49 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_died(t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&(infos->msg));
	printf("%ld ms %d %s", get_time(infos), philo->philo_nb + 1, "died\n");
	pthread_mutex_unlock(&(infos->msg));
	unlock_forks(infos);
}

static void	loop_last_meal(t_philo *philo, t_infos *infos, int nb_philos)
{
	int	i;

	while (!(infos->valid_infos == 1 || infos->nb_tot_meal == nb_philos)
		&& nb_philos != 0)
	{
		i = 0;
		pthread_mutex_lock(&(infos->check_last_meal));
		while (i < nb_philos && infos->valid_infos != 1)
		{
			if (get_time(infos) - philo[i].time_last_meal >= infos->time_to_die
				&& philo[i].philo_status != DONE)
			{
				infos->valid_infos = 1;
				philo_died(philo, infos);
			}
			++i;
		}
		pthread_mutex_unlock(&(infos->check_last_meal));
	}
}

static int	init_thread(t_philo *philo, int nb_philos, pthread_t *philo_thread)
{
	int	i;

	i = 0;
	get_time_beginning(philo[0].infos);
	while (i < nb_philos)
	{
		if (pthread_create(&philo_thread[i], NULL, &routine, &(philo[i])) != 0)
			return (pthread_create_error(philo, philo_thread, i));
		++i;
	}
	i = 0;
	loop_last_meal(philo, philo[0].infos, nb_philos);
	while (i < nb_philos)
	{
		if (pthread_join(philo_thread[i], NULL) != 0)
			pthread_join_error(philo[0].infos, i + 1);
		++i;
	}
	return (0);
}

int	ft_thread(t_philo *philo, int nb_philos)
{
	pthread_t		*philo_thread;

	if (ft_pthread_mutex_init(philo[0].infos) != 0)
	{
		philo[0].infos->infos_ft = -8;
		return (1);
	}
	philo_thread = malloc(sizeof(pthread_t) * (size_t)nb_philos);
	if (!philo_thread)
	{
		ft_pthread_mutex_destroy(philo[0].infos);
		philo[0].infos->infos_ft = -8;
		return (error_msg(4, "malloc error", 0));
	}
	init_thread(philo, nb_philos, philo_thread);
	ft_pthread_mutex_destroy(philo[0].infos);
	free(philo_thread);
	return (0);
}
