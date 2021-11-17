#include "philo.h"

int	args_are_digit(char **argv)
{
	int		i;
	int		j;
	
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == FALSE)
			{
				ft_putstr_fd("error: invalid argument\n", 2);
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int		nbr_overflow(char *arg, int nbr_to_compare)
{
	char	*temp;

	temp = ft_itoa(nbr_to_compare);
	if (ft_strcmp(arg, temp) != 0)
	{
		free(temp);
		return (TRUE);
	}
	else
	{
		free(temp);
		return (FALSE);
	}
}

int		is_overflow(t_data *philo, char **argv)
{
	if (nbr_overflow(argv[1], philo->philo_count))
		return (TRUE);
	if (nbr_overflow(argv[2], philo->time_to_die))
		return (TRUE);
	if (nbr_overflow(argv[3], philo->time_to_eat))
		return (TRUE);
	if (nbr_overflow(argv[4], philo->time_to_sleep))
		return (TRUE);	
	if (argv[5])
	{
		if (nbr_overflow(argv[5], philo->eat_count))
			return (TRUE);
	}
	return (FALSE);
}

int		put_valid_number_to_struct(t_data *philo, char **argv)
{
	init_struct(philo);
	philo->philo_count = ft_atoi(argv[1]);
	if (philo->philo_count == 0)
	{
		ft_putstr_fd("error: number of philosophers must be more than 0\n", 2);
		return (FALSE);
	}
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	if (is_overflow(philo, argv))
	{
		ft_putstr_fd("error: invalid argument\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
