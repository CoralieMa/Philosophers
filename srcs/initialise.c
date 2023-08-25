/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:36:53 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 16:32:31 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_philo	*initialise_philo(t_infos *infos)
{
	int		i;
	t_philo	*philo;

	if (infos->number_of_philosophers == 0 || infos->valid_infos == -1)
		return (NULL);
	philo = malloc (sizeof(t_philo) * (size_t)infos->number_of_philosophers);
	if (!philo)
	{
		free(infos->forks);
		printf("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		philo[i].philo_nb = i;
		philo[i].philo_status = THINK;
		philo[i].infos = infos;
		philo[i].nb_meal = 0;
		philo[i].time_last_meal = 0;
		++i;
	}
	return (philo);
}

static void	initialise_forks(t_infos *infos, int nb_philos)
{
	infos->forks = malloc(sizeof(pthread_mutex_t) * (size_t)(nb_philos));
	if (!infos->forks)
		infos->valid_infos = -2;
}

t_philo	*initialise_data(int argc, char **argv, t_infos *infos)
{
	infos->valid_infos = 0;
	infos->begin_time = 0;
	infos->nb_tot_meal = 0;
	infos->number_of_philosophers = ft_atoi(argv[1]);
	infos->time_to_die = (useconds_t)ft_atoi(argv[2]);
	infos->time_to_eat = (useconds_t)ft_atoi(argv[3]);
	infos->time_to_sleep = (useconds_t)ft_atoi(argv[4]);
	infos->number_of_times_each_philosopher_must_eat = -1;
	if (infos->number_of_philosophers <= 0 || (int)infos->time_to_die <= 0
		|| (int)infos->time_to_eat <= 0 || (int)infos->time_to_sleep <= 0)
		infos->valid_infos = -1;
	else
		initialise_forks(infos, infos->number_of_philosophers);
	if (infos->valid_infos == -2)
		return (NULL);
	if (argc == 6)
	{
		infos->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (infos->number_of_times_each_philosopher_must_eat <= 0)
		{
			free(infos->forks);
			infos->valid_infos = -1;
		}
	}
	return (initialise_philo(infos));
}
