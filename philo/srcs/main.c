#include "philo.h"



/*
main loop:
- get the time
- check if someone died

subtract actual_time - start_time to get the duration

*/





int	main(int argc, char **argv)
{
	t_data	data;

	if  (args_are_valid(argc, argv))
	{
		if (get_number_to_struct(&data, argv) == FALSE)
			return (0);
		printf("philo_count:%d\n", data.philo_count);
		printf("time_die:%d\n", data.time_die);
		printf("time_eat:%d\n", data.time_eat);
		printf("time_sleep:%d\n", data.time_sleep);
		printf("eat_count:%d\n", data.eat_count);
	}
	while (!data.died) //add eat count
	{
		data.time_actual = get_time_in_ms();
	}
	return (0);
}
