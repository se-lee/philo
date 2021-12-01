/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:21:01 by selee             #+#    #+#             */
/*   Updated: 2021/12/01 16:51:38 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	args_are_positive_nbr(char **argv)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		j = 0;
// 		while (argv[i][j])
// 		{
// 			if (ft_isdigit(argv[i][j]) == FALSE)
// 				return (FALSE);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (TRUE);
// }

int	args_are_positive_nbr(t_data *data)
{
	if (data->philo_count < 0)
		return (ERROR);
	if (data->time_to_die < 0)
		return (ERROR);
	if (data->time_to_eat < 0)
		return (ERROR);
	if (data->time_to_sleep < 0)
		return (ERROR);
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

int	parse(t_data *data, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
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
	if (args_are_positive_nbr(data) < 0)
		return (ERROR);
	return (TRUE);
}
