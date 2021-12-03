/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:38 by selee             #+#    #+#             */
/*   Updated: 2021/12/03 16:42:44 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_fork) != 0)
		return (ERROR);
	print_status(philo, "has taken a fork\n", FALSE);
	if (philo->id == 1)
	{
		if (philo->data->philo_count == 1)
			return (0);
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

int	release_forks(t_philo *philo)
{
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
	return (0);
}

int	philo_eating(t_philo *philo)
{
	if (take_forks(philo) == ERROR)
		return (ERROR);
	if (philo->data->philo_count == 1)
		return (ERROR);
	print_status(philo, "is eating\n", FALSE);
	if (pthread_mutex_lock(&philo->check_life) != 0)
		return (ERROR);
	philo->time_before_die = philo->data->time_actual
		+ philo->data->time_to_die;
	if (pthread_mutex_unlock(&philo->check_life) != 0)
		return (ERROR);
	wait_upto(philo->data, philo->data->time_to_eat);
	if (pthread_mutex_unlock(&philo->mutex_fork) != 0)
		return (ERROR);
	if (release_forks(philo) == ERROR)
		return (ERROR);
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
// printf("data.ready_activity: %d\n", philo->data->ready);
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
		if (philo->data->philo_count == 1)
			wait_upto(philo->data, LONG_MAX - philo->data->time_actual);
		philo_sleeping(philo);
	}
	if (pthread_mutex_lock(&philo->data->print_mutex) != 0)
		return ((void *)ERROR);
	philo->data->philo_finished++;
	if (pthread_mutex_unlock(&philo->data->print_mutex) != 0)
		return ((void *)ERROR);
//	usleep(); //to make sure pthreadjoin is started
	return (0);
}
