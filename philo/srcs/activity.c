#include "philo.h"

void	ft_sleep(t_data *data, int time_to_sleep)
{
	long	time;

	time = time_to_sleep + data->time_actual; // convert into timestamp because time_to_sleep is duration, not the actual time since 1970
	while (data->time_actual < time)
		usleep(200);
}

void	print_status(t_philo *philo, char *str)
{
	ft_putnbr_fd(philo->data->time_actual - philo->data->time_start, 1);
	write(1, ' ', 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, ' ', 1);
	ft_putstr_fd(str, 1);
}

void	eating_func(t_philo *philo)
{
	print_status(philo, "is eating\n");
	ft_sleep(philo->data, philo->data->time_eat);

}

void	sleeping_func(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_sleep(philo->data, philo->data->time_sleep);
}
