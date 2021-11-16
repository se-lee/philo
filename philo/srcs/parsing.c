#include "philo.h"

/*
0 ./philo 
1 number_of_philosophers 
2 time_to_die 
3 time_to_eat 
4 time_to_sleep 
5 [number_of_times_each_philosopher_must_eat]
*/

void	philo_activities(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->ready)
		usleep(500); //at least 500 usec
	if (philo->id % 2 == 0) // one group has to wait
		usleep(2000);
	while ((philo->data->eat_count == -1 || philo->eat_count < philo->data->eat_count)
		&& philo->data->died == 0)
	{
		eating_func;
		sleep_func;
	}
}

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
		i++;
	}
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
}

int		get_number_to_struct(t_data *philo, char **argv)
{
	init_struct(philo);
	philo->philo_count = ft_atoi(argv[1]);
	if (philo->philo_count == 0)
	{
		ft_putstr_fd("error: number of philosophers must be more than 0\n", 2);
		return (FALSE);
	}
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	if (check_overflow(philo, argv))
	{
		ft_putstr_fd("error\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
