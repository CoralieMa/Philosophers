/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/09 14:22:29 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(t_philo *philo, t_infos *infos, char *msg)
{
	pthread_mutex_lock(&(infos->msg));
	if (infos->valid_infos != 1)
		printf("%ld ms %d %s", get_time(infos), philo->philo_nb + 1, msg);
	pthread_mutex_unlock(&(infos->msg));
}

int	verification_dead(t_philo *philo, t_infos *infos, int a)
{
	if (philo->philo_status == EAT)
		return (0);
	if (infos->valid_infos != 0)
		return (1);
	if ((get_time(infos) - philo->time_last_meal > infos->time_to_die))
	{
		infos->valid_infos = 1;
		printf("%ld ms %d %s", get_time(infos), philo->philo_nb + 1, "died\n");
		philo->philo_status = DEAD;
		printf("%d--> %d  last_meal-> %ld time_to_sleep-> %d\n", philo->philo_nb + 1, a, philo->time_last_meal, infos->time_to_sleep);
		(void)a;
		return (1);
	}
	return (0);
}

static void	*exeption(t_philo *philo, t_infos *infos)
{
	if (infos->number_of_philosophers == 1)
	{
		print_msg(philo, infos, "has taken a fork\n");
		ft_msleep(philo, infos, infos->time_to_die);
		print_msg(philo, infos, "died\n");
	}
	return (NULL);
}

void	loop_routine(t_philo *philo, t_infos *infos)
{
	if (verification_dead(philo, infos, 10000) == 0
		|| philo->nb_meal != infos->number_of_times_each_philosopher_must_eat)
	{
		taking_forks(philo, infos);
		eating(philo, infos);
		returning_fork(philo, infos);
		sleeping(philo, infos);
	}
	else
		philo->philo_status = DONE;
	if (philo->nb_meal == infos->number_of_times_each_philosopher_must_eat)
		philo->philo_status = DONE;
}

void	*routine(void *arg)
{
	t_philo	philo;
	t_infos	*infos;

	philo = *(t_philo *)arg;
	infos = philo.infos;
	if (philo.infos->number_of_philosophers < 2)
		return (exeption(&philo, infos));
	if (philo.philo_nb % 2 != 0)
		ft_msleep(&philo, infos, infos->time_to_eat / 2);
	while (infos->valid_infos == 0 && philo.philo_status != DONE)
		loop_routine(&philo, infos);
	return (NULL);
}
