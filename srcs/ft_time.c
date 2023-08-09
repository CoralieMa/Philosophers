/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:02 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/09 11:58:55 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long	get_last_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, DST_NONE);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	ft_msleep(t_philo *philo, t_infos *infos, int ms)
{
	int	target_time;
	int	last_time;

	last_time = get_last_time();
	target_time = last_time + ms;
	while (last_time < target_time && infos->valid_infos != 1)
	{
		if (verification_dead(philo, infos, 10) != 0)
			return ;
		last_time = get_last_time();
		usleep(10);
	}
}

void	get_time_beginning(t_infos *infos)
{
	struct timeval	tv;

	gettimeofday(&tv, DST_NONE);
	infos->begin_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
}

long	get_time(t_infos *infos)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, DST_NONE);
	time = ((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - infos->begin_time;
	return (time);
}
