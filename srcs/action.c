/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:13:33 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/09 14:32:55 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	returning_fork(t_philo *philo, t_infos *infos)
{
	pthread_mutex_unlock(&(infos->forks[philo->philo_nb]));
	print_msg(philo, infos, "return l fork\n");
	if ((infos->number_of_philosophers -1) != philo->philo_nb)
		pthread_mutex_unlock(&(infos->forks[philo->philo_nb + 1]));
	else
		pthread_mutex_unlock(&(infos->forks[0]));
	print_msg(philo, infos, "return r fork\n");
}

void	sleeping(t_philo *philo, t_infos *infos)
{
	if (verification_dead(philo, infos, 4) != 0)
		return ;
	print_msg(philo, infos, "is sleeping\n");
	ft_msleep(philo, infos, infos->time_to_sleep);
	if (verification_dead(philo, infos, 40) != 0)
		return ;
	print_msg(philo, infos, "is thinking\n");
	philo->philo_status = THINK;
}

void	eating(t_philo *philo, t_infos *infos)
{
	print_msg(philo, infos, "is eating\n");
	philo->philo_status = EAT;
	philo->time_last_meal = get_time(infos);
	ft_msleep(philo, infos, infos->time_to_eat);
	philo->nb_meal += 1;
	philo->philo_status = SLEEP;
	if (philo->nb_meal == infos->number_of_times_each_philosopher_must_eat)
		philo->philo_status = DONE;
}

void	taking_forks(t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&(infos->forks[philo->philo_nb]));
	if (verification_dead(philo, infos, 51) != 0)
		return ;
	print_msg(philo, infos, "has taken a fork l\n");
	if ((infos->number_of_philosophers -1) != philo->philo_nb)
		pthread_mutex_lock(&(infos->forks[philo->philo_nb + 1]));
	else
		pthread_mutex_lock(&(infos->forks[0]));
	if (verification_dead(philo, infos, 52) != 0)
		return ;
	print_msg(philo, infos, "has taken a fork r\n");
}
