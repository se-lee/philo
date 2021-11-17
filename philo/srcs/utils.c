#include "philo.h"

void	*malloc_protected(int size, int count)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
	{
		perror("malloc failure");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	print_status(t_philo *philo, char *str, int in_main)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	ft_putnbr_fd(philo->data->time_actual - philo->data->time_start, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
	if (in_main == TRUE)
		philo->data->died = 1;
	pthread_mutex_unlock(&philo->data->print_mutex);
}
