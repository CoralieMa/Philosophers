/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:25 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/26 11:00:09 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_infos	infos;

	if (input_not_valid(argc, argv) != 1)
		return (0);
	infos = initialise_data(argc, argv);
	if (infos.valid_infos == -1)
		return (error_msg(3, "input not valid", 0));
	if (initialise_philo(&infos) < 0)
		return (error_msg(4, "malloc error", 0));
	ft_thread(&infos);
	free(infos.philo);
	return (0);
}
