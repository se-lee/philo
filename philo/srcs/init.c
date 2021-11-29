/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:41 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 10:20:47 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_data *data)
{
	data->philo_count = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->eat_count = -1;
	data->died = 0;
	data->ready = 0;
	data->philo_finished = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ERROR);
	return (0);
}

int	init_all_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].times_eaten = 0;
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread, NULL,
				philo_activities, &data->philo[i]) != 0)
			return (ERROR);
		if (pthread_mutex_init(&data->philo[i].mutex_fork, NULL) != 0)
			return (ERROR);
		if (pthread_mutex_init(&data->philo[i].check, NULL) != 0)
			return (ERROR);
		data->philo[i].time_before_die = INT64_MAX;
		i++;
	}
	data->time_start = get_time_in_ms();
	data->time_actual = get_time_in_ms();
	data->ready = 1;
	return (0);
}
