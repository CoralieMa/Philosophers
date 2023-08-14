/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/14 13:27:10 by cmartino         ###   ########.fr       */
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
	if (infos->valid_infos != 0)
		return (1);
	pthread_mutex_lock(&(infos->check_last_meal));
	if ((get_time(infos) - philo->time_last_meal > infos->time_to_die))
	{
		infos->valid_infos = 1;
		unlock_forks(infos);
		printf("%ld ms %d %s ->%d", get_time(infos), philo->philo_nb + 1, "died\n", a);
		philo->philo_status = DEAD;
		// (void)a;
		return (1);
	}
	pthread_mutex_unlock(&(infos->check_last_meal));
	return (0);
}

static void	*exeption(t_philo *philo, t_infos *infos)
{
	if (infos->number_of_philosophers == 1)
	{
		print_msg(philo, infos, "has taken a fork\n");
		ft_msleep(philo, infos, infos->time_to_die);
		print_msg(philo, infos, "died\n");
		infos->valid_infos = 1;
	}
	return (NULL);
}

void	loop_routine(t_philo *philo, t_infos *infos)
{
	if (verification_dead(philo, infos, 10000) == 0
		|| philo->nb_meal == infos->number_of_times_each_philosopher_must_eat)
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
	t_philo	*philo;
	t_infos	*infos;

	philo = (t_philo *)arg;
	infos = philo->infos;
	philo->infos->test = 8;
	if (philo->infos->number_of_philosophers < 2)
		return (exeption(philo, infos));
	if (philo->philo_nb % 2 != 0)
	{
		ft_msleep(philo, infos, infos->time_to_eat / 2);
	}
	while (infos->valid_infos == 0 && philo->philo_status != DONE)
		loop_routine(philo, infos);
	infos->valid_infos = 1;
	return (NULL);
}
