#include "philo.h"

void	ft_sleep(t_data *data, int time_to_wait)
{
	long	time;

	time = time_to_wait + data->time_actual; // convert into timestamp because time_to_sleep is duration, not the actual time since 1970
	while (data->time_actual < time && !data->died)
		usleep(200);
}

/* lock print_mutext so that it doesnt write at the same moment */
void	print_status(t_philo *philo, char *str)
{
	if (!philo->data->died)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_putnbr_fd(philo->data->time_actual - philo->data->time_start, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(str, 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	eating_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_status(philo, "has taken a fork\n");
	if (philo->id == 1)
		pthread_mutex_lock(&philo->data->philo[philo->data->philo_count].mutex_fork);
	else
		pthread_mutex_lock(&philo->data->philo[philo->id - 2].mutex_fork); //philo before you
	print_status(philo, "has taken a fork\n");
	print_status(philo, "is eating\n");
	philo->time_before_die = philo->data->time_actual + philo->data->time_die;
	ft_sleep(philo->data, philo->data->time_eat);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->data->philo[philo->id - 2].mutex_fork); //philo before you
}


void	sleeping_func(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_sleep(philo->data, philo->data->time_sleep);
}

void	*philo_activities(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->ready)
		usleep(500); //at least 500 usec
	philo->time_before_die = philo->data->time_actual + philo->data->time_die;
	if (philo->id % 2 == 0) // one group has to wait
		usleep(2000);
	while ((philo->data->eat_count == -1 || philo->eat_count < philo->data->eat_count)
		&& philo->data->died == 0)
	{
		eating_func(philo);
		sleeping_func(philo);
	}
	return (NULL);
}
