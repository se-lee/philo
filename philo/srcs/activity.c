#include "philo.h"

void	wait_upto(t_data *data, int time_to_wait)
{
	long	time;

	time = time_to_wait + data->time_actual;
	while (data->time_actual < time && !data->died)
		usleep(200);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_status(philo, "has taken a fork\n", FALSE);
	if (philo->id == 1)
		pthread_mutex_lock(&philo->data->philo[philo->data->philo_count - 1].mutex_fork);
	else
		pthread_mutex_lock(&philo->data->philo[philo->id - 2].mutex_fork); //philo before you
	print_status(philo, "has taken a fork\n", FALSE);
	print_status(philo, "is eating\n", FALSE);
	pthread_mutex_lock(&philo->check);
	philo->time_before_die = philo->data->time_actual + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->check);
	wait_upto(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_fork);
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->data->philo[philo->data->philo_count - 1].mutex_fork);
	else
		pthread_mutex_unlock(&philo->data->philo[philo->id - 2].mutex_fork); //philo before you
	philo->times_ate++;
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
	philo->time_before_die = philo->data->time_actual + philo->data->time_to_die;
	if (philo->id % 2 == 0)
		usleep(2000);
	while ((philo->data->eat_count == -1 || philo->times_ate < philo->data->eat_count)
		&& philo->data->died == 0)
	{
		philo_eating(philo);
		philo_sleeping(philo);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->data->philo_finished++;
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}
