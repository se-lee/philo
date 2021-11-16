#include "philo.h"

/*
0 ./philo 
1 number_of_philosophers 
2 time_to_die 
3 time_to_eat 
4 time_to_sleep 
5 [number_of_times_each_philosopher_must_eat]
*/

void	init_philo(t_philo *philo, int i)
{
	philo->id = i;
//	philo->thread =
	// pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	// pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

	init_struct(philo->data);
}

void	init_all_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= data->philo_count)
	{
		init_philo(philo, i);
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
