/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:25 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/25 11:30:39 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_infos	infos;

	if (input_not_valid(argc, argv) != 1)
		return (0);
	infos.infos_ft = 0;
	philos = initialise_data(argc, argv, &infos);
	if (infos.valid_infos == -2)
		return (error_msg(4, "malloc error", 0));
	if (!philos)
		return (0);
	if (infos.valid_infos == -1)
		return (error_msg(3, "input not valid", 0));
	ft_thread(philos, philos[0].infos->number_of_philosophers);
	ft_free_struct(&infos, philos);
	if (infos.infos_ft == -8)
		return (1);
	return (0);
}
