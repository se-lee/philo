#include "philo.h"

/*
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
*/

long	get_time_in_ms(void)
{
	struct timeval	tp;
	long	ret;

	gettimeofday(&tp, NULL);
	ret = (long)tp.tv_sec * 1000 + (long)tp.tv_usec / 1000;

	return (ret);
}
