/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:14:39 by cmartino          #+#    #+#             */
/*   Updated: 2023/08/28 10:02:20 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*wich_arg(int i)
{
	if (i == 1)
		return ("number_of_philosophers");
	else if (i == 2)
		return ("time_to_die");
	else if (i == 3)
		return ("time_to_eat");
	else if (i == 4)
		return ("time_to_sleep");
	else if (i == 5)
		return ("[optional] number_of_times_each_philosopher_must_eat");
	return (NULL);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	error_msg(int type, char *msg, int i)
{
	if (type == 1)
	{
		printf("%s", msg);
		printf("The program should take the following arguments:\n");
		printf("-> number_of_philosophers\n-> time_to_die\n-> time_to_eat\n-> ");
		printf("time_to_sleep\n-> [number_of_times_each_philosopher_must_eat]\n");
	}
	if (type == 2)
		printf("%s : %s must be a positive number\n", msg, wich_arg(i));
	if (type == 3)
		printf("%s\n", msg);
	if (type == 4)
	{
		printf("%s\n", msg);
		return (1);
	}
	return (0);
}

static int	input_not_numeric(int argc, char **argv)
{
	int	i;
	int	j;
	int	stop;
	int	valid;

	i = 1;
	valid = 1;
	while (i < argc)
	{
		j = 0;
		stop = 1;
		while (argv[i][j] && stop == 1)
		{
			if (!ft_isdigit(argv[i][j]))
			{
				valid = error_msg(2, argv[i], i);
				stop = 0;
			}
			++j;
		}
		++i;
	}
	return (valid);
}

int	input_not_valid(int argc, char **argv)
{
	if (argc < 5)
		return (error_msg(1, "Too few arguments\n", 0));
	if (argc > 6)
		return (error_msg(1, "Too many arguments\n", 0));
	return (input_not_numeric(argc, argv));
}
