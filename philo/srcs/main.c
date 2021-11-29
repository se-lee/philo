/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:55 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 15:09:09 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count && !data->died)
	{
		data->time_actual = get_time_in_ms();
		if (pthread_mutex_lock(&data->philo->check) != 0)
			return (ERROR); //check if the philo is dead or not
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
		return (ERROR);
	}
	data.philo = malloc(sizeof(t_philo) * data.philo_count);
	if (!data.philo)
		return (ERROR);
	init_all_philo(&data);
	while (!data.died && data.philo_finished != data.philo_count)
		main_loop(&data);
	data.died = 1; // if data.died is 1, all the philos will stop what they are doing. for security
	i = 0;
	while (pthread_join(data.philo[i].thread, NULL))
	{
		if (pthread_mutex_destroy(&data.philo[i].mutex_fork))
			return (ERROR);
		data.time_actual = get_time_in_ms(); //need to update this otherwise philos can be stuck in wait_upto
		i++;
	}
	free(data.philo);
	return (0);
}

/*
init_struct: initialize data before malloc philo
mallocing the philo struct - it carries info about each philo

two groups: only if the total
even number id / odd number id

odd number : group changing
(thinking time gets longer)

- gettimeofday: 
if in activity function, every philo carries out the process
(eg. 1000 philos)
so rather than having gettimeofday func in activity, only do in main loop so that
each thread can look up the value instead of redoing it (to optimize)

- having *data inside each philo:
to have access to neighbors (through data)

- mutex example (with lever door)
- mutex lock
- fork gets available (=unlock)


*/