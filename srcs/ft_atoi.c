/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:27:53 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/02 14:16:08 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int					nb;
	int					i;

	i = 0;
	nb = 0;
	if (!str[i])
		return (-1);
	while (str[i] == '0')
		++i;
	while (ft_isdigit(str[i]) && nb >= 0)
		nb = nb * 10 + (str[i ++] - 48);
	if ((str[i] && !ft_isdigit(str[i])) || nb < 0)
		nb = -1;
	return (nb);
}
