/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:21:01 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 10:27:11 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_are_positive_nbr(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	is_overflow(char *arg, int nbr_to_compare)
{
	char	*temp;

	temp = ft_itoa(nbr_to_compare);
	if (ft_strcmp(arg, temp) != 0)
	{
		free(temp);
		return (TRUE);
	}
	else
	{
		free(temp);
		return (FALSE);
	}
}

int	args_overflow(t_data *data, char **argv)
{
	if (is_overflow(argv[1], data->philo_count))
		return (TRUE);
	if (is_overflow(argv[2], data->time_to_die))
		return (TRUE);
	if (is_overflow(argv[3], data->time_to_eat))
		return (TRUE);
	if (is_overflow(argv[4], data->time_to_sleep))
		return (TRUE);
	if (argv[5])
	{
		if (is_overflow(argv[5], data->eat_count))
			return (TRUE);
	}
	return (FALSE);
}

int	parse(t_data *data, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (ERROR);
	if (!args_are_positive_nbr(argv))
		return (ERROR);
	init_struct(data);
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count == 0)
		return (ERROR);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
	if (args_overflow(data, argv))
		return (ERROR);
	return (TRUE);
}
