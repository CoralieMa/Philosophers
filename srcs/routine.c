/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:37:03 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/26 11:02:47 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	philo;
	t_philo	*result;

	result = malloc(sizeof(philo));
	philo = *(t_philo *)arg;
	printf("Hello philo n. -> %d\n", philo.philo_nb);
	philo.philo_nb = philo.philo_nb * 10;
	*result = philo;
	return ((void *)result);
}
