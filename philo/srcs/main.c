/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:55 by selee             #+#    #+#             */
/*   Updated: 2021/12/03 17:40:59 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count && data->died == FALSE)
	{
		data->time_actual = get_time_in_ms();
		if (pthread_mutex_lock(&data->philo->check_life) != 0)
			return (ERROR);
		if ((data->time_actual >= data->philo[i].time_before_die)
			&& (data->eat_count == -1
				|| data->philo[i].times_eaten < data->eat_count))
			print_status(&data->philo[i], "died\n", TRUE);
		if (pthread_mutex_unlock(&data->philo->check_life) != 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	init_struct(&data);
	if (parse(&data, argc, argv) == ERROR)
	{
		ft_putstr_fd("invalid argument(s)\n", 2);
		return (ERROR);
	}
	data.philo = malloc(sizeof(t_philo) * data.philo_count);
	if (!data.philo)
		return (ERROR);
	if (init_all_philo(&data) == ERROR)
		return (ERROR);
	while (data.died == FALSE && data.philo_finished != data.philo_count)
		main_loop(&data);
	data.died = TRUE;
	i = 0;
	usleep(1000);
	while (pthread_join(data.philo[i].thread, NULL))
	{
		if (pthread_mutex_destroy(&data.philo[i].mutex_fork) != 0)
			return (ERROR);
		if (pthread_mutex_destroy(&data.philo[i].check_life) != 0)
			return (ERROR);
		data.time_actual = get_time_in_ms();
		i++;
	}
	free(data.philo);
	return (0);
}
