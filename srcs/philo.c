/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:25 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/09 10:24:59 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_infos	infos;

	if (input_not_valid(argc, argv) != 1)
		return (0);
	philos = initialise_data(argc, argv, &infos);
	if (!philos)
		return (0);
	if (philos[0].infos->valid_infos == -1)
		return (error_msg(3, "input not valid", 0));
	ft_thread(philos, philos[0].infos->number_of_philosophers);
	//free
	return (0);
}
