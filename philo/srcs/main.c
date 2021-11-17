#include "philo.h"

/*
0 ./philo 
1 number_of_philosophers 
2 time_to_die 
3 time_to_eat 
4 time_to_sleep 
5 [number_of_times_each_philosopher_must_eat]

main loop:
- get the time
- check if someone died

subtract actual_time - start_time to get th
e duration
*/

void	main_loop(t_data *data)
{
	int		i;
	
	i = 0;
	while (i < data->philo_count && !data->died)// && data->philo_finished != data->philo_count)
	{
		data->time_actual = get_time_in_ms();
		pthread_mutex_lock(&data->philo->check);
		if ((data->time_actual > data->philo[i].time_before_die) 
			&& (data->eat_count == -1 || data->philo[i].eat_count < data->eat_count))
			print_status(&data->philo[i], "died\n", TRUE);
		pthread_mutex_unlock(&data->philo->check);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if  (args_are_valid(argc, argv))
	{
		if (get_number_to_struct(&data, argv) == FALSE)
			return (0);
		data.philo = malloc(sizeof(t_philo) * data.philo_count);
		init_philo(&data);
		while (!data.died && data.philo_finished != data.philo_count)
			main_loop(&data);
	}
		data.died = 1;
		i = 0;
		while (pthread_join(data.philo[i].thread, NULL))
		{
			pthread_mutex_destroy(&data.philo[i].mutex_fork);
			data.time_actual = get_time_in_ms();
			i++;
		}
	return (0);
}
