/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:55 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 11:43:54 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
subtract actual_time - start_time to get the duration

Todo
1) handle a case where there is only one philosopher
2) protect functions with initializing threads/mutex, get time...what else?
	(when creating threads/mutex fails)
4) when do i free?

check if the philo is one

*/

int	main_loop(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_count && !data->died)
	{
		data->time_actual = get_time_in_ms();
		if (pthread_mutex_lock(&data->philo->check) != 0)
			return (ERROR);
		if ((data->time_actual > data->philo[i].time_before_die)
			&& (data->eat_count == -1
				|| data->philo[i].times_eaten < data->eat_count))
			print_status(&data->philo[i], "died\n", TRUE);
		if (pthread_mutex_unlock(&data->philo->check) != 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (parse(&data, argc, argv) == ERROR)
	{
		ft_putstr_fd("invalid argument(s)\n", 2);
		return (-1);
	}
	data.philo = malloc_protected(sizeof(t_philo), data.philo_count);
	init_all_philo(&data);
	while (!data.died && data.philo_finished != data.philo_count)
		main_loop(&data);
	data.died = 1;
	i = 0;
	while (pthread_join(data.philo[i].thread, NULL))
	{
		if (pthread_mutex_destroy(&data.philo[i].mutex_fork))
			return (ERROR);
		data.time_actual = get_time_in_ms();
		i++;
	}
	return (0);
}
