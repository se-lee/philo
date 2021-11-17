#include "philo.h"

void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		pthread_create(&data->philo[i].thread, NULL, philo_activities, &data->philo[i]);
		pthread_mutex_init(&data->philo[i].mutex_fork, NULL);
		pthread_mutex_init(&data->philo[i].check, NULL);
		data->philo[i].time_before_die = INT64_MAX;
		i++;
	}
	data->time_start = get_time_in_ms();
	data->time_actual = get_time_in_ms();
	data->ready = 1;
}

void	init_struct(t_data *data)
{
	data->philo_count = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->time_sleep = 0;
	data->eat_count = -1;
	data->died = 0;
	data->ready = 0;
	data->philo_finished = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
}
