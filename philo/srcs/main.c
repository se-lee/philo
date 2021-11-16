#include "philo.h"



/*
main loop:
- get the time
- check if someone died


subtract actual_time - start_time to get the duration

*/





int	main(int argc, char **argv)
{
	t_data	philo;

	if  (args_are_valid(argc, argv))
	{
		if (get_number_to_struct(&philo, argv) == FALSE)
			return (0);
		printf("philo_count:%d\n", philo.philo_count);
		printf("time_die:%d\n", philo.time_die);
		printf("time_eat:%d\n", philo.time_eat);
		printf("time_sleep:%d\n", philo.time_sleep);
		printf("eat_count:%d\n", philo.eat_count);
	}
	return (0);
}
