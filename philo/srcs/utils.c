/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:21:09 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 10:24:54 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
