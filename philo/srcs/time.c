/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:21:04 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 10:33:31 by selee            ###   ########lyon.fr   */
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
