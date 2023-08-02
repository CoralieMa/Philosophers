/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:02 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/02 14:05:59 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_time_beginning(t_infos *infos)
{
	struct timeval tv;

	gettimeofday(&tv, DST_NONE);
	infos->start_sec = (int)tv.tv_sec;
	infos->start_msec = tv.tv_usec / 1000;
}

int	get_time(t_infos *infos)
{
	int		sec;
	int		msec;
	int		time;
	struct	timeval tv;

	gettimeofday(&tv, DST_NONE);
	sec = (int)tv.tv_sec - infos->start_sec;
	msec = ((tv.tv_usec / 1000) - infos->start_msec);
	time = sec * 1000;
	if (msec >= 0)
		time += msec;
	else
	{
		time -= 1000;
		time += (1000 - msec);
	}
	return time;
}
