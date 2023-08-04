/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:02 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/04 12:09:05 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_msleep(int ms)
{
	int	i;
	int	time;

	i = 0;
	time = 10 * ms;
	while(++i <= time)
		usleep(100);
}

void	get_time_beginning(t_infos *infos)
{
	struct timeval tv;

	gettimeofday(&tv, DST_NONE);
	infos->start_sec = (int)tv.tv_sec;
	infos->start_msec = tv.tv_usec;
}

long	get_time(t_infos *infos)
{
	long		sec;
	int		usec;
	long		time;
	struct	timeval tv;

	gettimeofday(&tv, DST_NONE);
	sec = tv.tv_sec - infos->start_sec;
	usec = (tv.tv_usec - infos->start_msec);
	time = sec * 1000000;
	if (usec >= 0)
		time += usec;
	else
	{
		time -= 1000000;
		time += (1000000 + usec);
	}
	return (time / 1000);
}
