#include "philo.h"

void	ft_wait(t_data *data, int time_to_wait)
{
	long	time;

	time = time_to_wait + data->time_actual; // convert into timestamp because time_to_sleep is duration, not the actual time since 1970
	while (data->time_actual < time && !data->died)
		usleep(200);
}

/* lock print_mutext so that it doesnt write at the same moment */
void	eating_func(t_philo *philo)
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
	philo->time_before_die = philo->data->time_actual + philo->data->time_die;
	pthread_mutex_unlock(&philo->check);
	ft_wait(philo->data, philo->data->time_eat);
	pthread_mutex_unlock(&philo->mutex_fork);
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->data->philo[philo->data->philo_count - 1].mutex_fork);
	else
		pthread_mutex_unlock(&philo->data->philo[philo->id - 2].mutex_fork); //philo before you
	philo->eat_count++;
}


void	sleeping_func(t_philo *philo)
{
	print_status(philo, "is sleeping\n", FALSE);
	ft_wait(philo->data, philo->data->time_sleep);
	print_status(philo, "is thinking\n", FALSE);
}

void	*philo_activities(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->ready)
		usleep(500); //at least 500 usec
	// pthread_mutex_lock(&philo->check);
	philo->time_before_die = philo->data->time_actual + philo->data->time_die;
	// pthread_mutex_unlock(&philo->check);
	if (philo->id % 2 == 0) // one group has to wait
		usleep(2000);
	while ((philo->data->eat_count == -1 || philo->eat_count < philo->data->eat_count)
		&& philo->data->died == 0)
	{
		eating_func(philo);
		sleeping_func(philo);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->data->philo_finished++;
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}
