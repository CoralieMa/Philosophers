/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:02 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 13:53:17 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_last_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, DST_NONE);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	ft_msleep(t_infos *infos, int ms)
{
	long	target_time;
	long	last_time;

	last_time = get_last_time();
	if (last_time == -1)
		return ;
	target_time = last_time + ms;
	while (last_time < target_time && infos->valid_infos != 1)
	{
		last_time = get_last_time();
		if (last_time == -1)
			return ;
		usleep(100);
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

	time = get_last_time();
	time = (time - infos->begin_time);
	return (time);
}
