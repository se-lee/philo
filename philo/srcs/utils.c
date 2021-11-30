/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:21:09 by selee             #+#    #+#             */
/*   Updated: 2021/11/30 14:28:44 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tp;
	long			ret;

	if (gettimeofday(&tp, NULL) < 0)
		return (ERROR);
	ret = (long)tp.tv_sec * 1000 + (long)tp.tv_usec / 1000;
	return (ret);
}

int	print_status(t_philo *philo, char *str, int in_main)
{
	if (pthread_mutex_lock(&philo->data->print_mutex) != 0)
		return (ERROR);
	if (philo->data->died == 1)
	{
		if (pthread_mutex_unlock(&philo->data->print_mutex))
			return (ERROR);
		return (0);
	}
	ft_putnbr_fd(philo->data->time_actual - philo->data->time_start, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
	if (in_main == TRUE)
		philo->data->died = 1;
	if (pthread_mutex_unlock(&philo->data->print_mutex) != 0)
		return (ERROR);
	return (0);
}

void	wait_upto(t_data *data, long time_to_wait)
{
	long	time;

	time = time_to_wait + data->time_actual;
	while (data->time_actual < time && !data->died)
		usleep(200);
}
