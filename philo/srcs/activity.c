#include "philo.h"

void	wait_upto(t_data *data, int time_to_wait)
{
	long	time;

	time = time_to_wait + data->time_actual;
	while (data->time_actual < time && !data->died)
		usleep(200);
}

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_fork) != 0)
		return (ERROR);
	print_status(philo, "has taken a fork\n", FALSE);
	if (philo->id == 1)
	{
		if (pthread_mutex_lock(&philo->data->philo
				[philo->data->philo_count - 1].mutex_fork) != 0)
			return (ERROR);
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->philo
				[philo->id - 2].mutex_fork) != 0)
			return (ERROR);
	}
	print_status(philo, "has taken a fork\n", FALSE);
	return (0);
}

int	philo_eating(t_philo *philo)
{
	if (take_forks(philo) == ERROR)
		return (ERROR);
	print_status(philo, "is eating\n", FALSE);
	if (pthread_mutex_lock(&philo->check) != 0)
		return (ERROR);
	philo->time_before_die = philo->data->time_actual
		+ philo->data->time_to_die;
	if (pthread_mutex_unlock(&philo->check) != 0)
		return (ERROR);
	wait_upto(philo->data, philo->data->time_to_eat);
	if (pthread_mutex_unlock(&philo->mutex_fork) != 0)
		return (ERROR);
	if (philo->id == 1)
	{
		if (pthread_mutex_unlock(&philo->data->philo
				[philo->data->philo_count - 1].mutex_fork) != 0)
			return (ERROR);
	}
	else
	{
		if (pthread_mutex_unlock(
				&philo->data->philo[philo->id - 2].mutex_fork) != 0)
			return (ERROR);
	}
	philo->times_eaten++;
	return (0);
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping\n", FALSE);
	wait_upto(philo->data, philo->data->time_to_sleep);
	print_status(philo, "is thinking\n", FALSE);
}

void	*philo_activities(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->ready)
		usleep(500);
	philo->time_before_die = philo->data->time_actual
		+ philo->data->time_to_die;
	if (philo->id % 2 == 0)
		usleep(2000);
	while ((philo->data->eat_count == -1
			|| philo->times_eaten < philo->data->eat_count)
		&& philo->data->died == 0)
	{
		philo_eating(philo);
		philo_sleeping(philo);
	}
	if (pthread_mutex_lock(&philo->data->print_mutex) != 0)
		return ((void *)ERROR);
	philo->data->philo_finished++;
	if (pthread_mutex_unlock(&philo->data->print_mutex) != 0)
		return ((void *)ERROR);
	return (0);
}
