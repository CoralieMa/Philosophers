/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 16:28:52 by cmartino         ###   ########.fr       */
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

int	verification_dead(t_philo *philo, t_infos *infos)
{
	if (philo->philo_status == DONE)
		return (0);
	pthread_mutex_lock(&(infos->check_last_meal));
	if (infos->valid_infos == 1)
	{
		pthread_mutex_unlock(&(infos->check_last_meal));
		return (1);
	}
	if ((get_time(infos) - philo->time_last_meal > infos->time_to_die))
	{
		infos->valid_infos = 1;
		unlock_forks(infos);
		pthread_mutex_lock(&(infos->msg));
		printf("%ld ms %d %s", get_time(infos), philo->philo_nb + 1, "died\n");
		pthread_mutex_unlock(&(infos->msg));
		philo->philo_status = DEAD;
		pthread_mutex_unlock(&(infos->check_last_meal));
		return (1);
	}
	pthread_mutex_unlock(&(infos->check_last_meal));
	return (0);
}

static void	*exception(t_philo *philo, t_infos *infos)
{
	if (infos->number_of_philosophers == 1)
	{
		print_msg(philo, infos, "has taken a fork\n");
		ft_msleep(infos, infos->time_to_die);
		print_msg(philo, infos, "died\n");
		infos->valid_infos = 1;
	}
	return (NULL);
}

void	loop_routine(t_philo *philo, t_infos *infos)
{
	if (verification_dead(philo, infos) == 0
		&& philo->philo_status != DONE)
	{
		taking_forks(philo, infos);
		eating(philo, infos);
		returning_fork(philo, infos);
		sleeping(philo, infos);
	}
	if (philo->nb_meal == infos->number_of_times_each_philosopher_must_eat)
	{
		philo->philo_status = DONE;
		infos->valid_infos = 25;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_infos	*infos;

	philo = (t_philo *)arg;
	infos = philo->infos;
	if (philo->infos->number_of_philosophers < 2)
		return (exception(philo, infos));
	if (philo->philo_nb % 2 != 0)
		ft_msleep(infos, infos->time_to_eat / 2);
	while (infos->valid_infos != 1 && philo->philo_status != DONE)
		loop_routine(philo, infos);
	++infos->nb_tot_meal;
	return (NULL);
}
