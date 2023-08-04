/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:25 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/04 12:05:07 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_infos	infos;

	get_time_beginning(&infos);
	printf("%ldms\n", get_time(&infos));
	ft_msleep(1);
	printf("%ldms\n", get_time(&infos));
	ft_msleep(4);
	printf("%ldms\n", get_time(&infos));
	ft_msleep(20);
	printf("%ldms\n", get_time(&infos));
	return (0);
	
	if (input_not_valid(argc, argv) != 1)
		return (0);
	philos = initialise_data(argc, argv, &infos);
	if (philos[0].infos->valid_infos == -1)
		return (error_msg(3, "input not valid", 0));
	ft_thread(philos, philos[0].infos->number_of_philosophers);
	//free + mutex_destroy
	return (0);
}
