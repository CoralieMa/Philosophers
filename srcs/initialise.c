/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:36:53 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/24 10:43:24 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialise_philo(t_infos *infos)
{
	int		i;
	t_philo	*philo;

	philo = malloc (sizeof(t_philo) * (size_t)infos->number_of_philosophers);
	if (!philo)
		return (-1);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		philo[i].philo_nb = i + 1;
		philo[i].philo_status = THINK;
		philo[i].left_fork = 1;
		philo[i].right_fork = 1;
		++i;
	}
	infos->philo = philo;
	return (0);
}

t_infos	initialise_data(int argc, char **argv)
{
	t_infos	infos;

	infos.valid_infos = 0;
	infos.number_of_philosophers = ft_atoi(argv[1]);
	infos.time_to_die = ft_atoi(argv[2]);
	infos.time_to_eat = ft_atoi(argv[3]);
	infos.time_to_sleep = ft_atoi(argv[4]);
	if (infos.number_of_philosophers < 0 || infos.time_to_die < 0
		|| infos.time_to_eat < 0 || infos.time_to_sleep < 0)
		infos.valid_infos = -1;
	if (argc == 6)
	{
		infos.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (infos.number_of_times_each_philosopher_must_eat < 0)
			infos.valid_infos = -1;
	}
	else
		infos.number_of_times_each_philosopher_must_eat = -1;
	return (infos);
}
