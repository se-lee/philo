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
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

// int		nbr_overflow(char *arg, int nbr_to_compare)
// {
// 	char	*temp;

// 	temp = itoa(nbr_to_compare);
// 	if (ft_strcmp(arg, temp) != 0)
// 	{
// 		free(temp);
// 		return (TRUE);
// 	}
// 	else
// 	{
// 		free(temp);
// 		return (FALSE);
// 	}
// }

int		check_overflow(t_data *philo, char **argv)
{
	// int		result;

	// nbr_overflow(argv[1], philo->philo_count);
	
	char	*temp;
	temp = ft_itoa(philo->philo_count);
	if (ft_strcmp(argv[1], temp) != 0)
		return (TRUE);
	free(temp);
	temp = ft_itoa(philo->time_die);
	if (ft_strcmp(argv[2], temp) != 0)
		return (TRUE);
	free(temp);
	temp = ft_itoa(philo->time_eat);
	if (ft_strcmp(argv[3], temp) != 0)
		return (TRUE);
	free(temp);
	temp = ft_itoa(philo->time_sleep);
	if (ft_strcmp(argv[4], temp) != 0)
	{
		free(temp);	
		return (TRUE);	
	}
	if (argv[5])
	{
		temp = ft_itoa(philo->eat_count);
		if (ft_strcmp(argv[5], temp) != 0)
		{
			free(temp);
			return (TRUE);
		}
	}
	return (FALSE);
}

int		args_are_valid(int argc, char **argv)
{
	if (!args_are_digit(argv))
	{
		ft_putstr_fd("error: argument not numeric\n", 2);
		return (FALSE);
	}
	if (argc != 5 && argc != 6)
	{
		if (argc < 5)
			ft_putstr_fd("error: too few arguments\n", 2);
		else
			ft_putstr_fd("error: too many arguments\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int		get_number_to_struct(t_data *philo, char **argv)
{
	init_struct(philo);
	philo->philo_count = ft_atoi(argv[1]);
	if (philo->philo_count == 0)
	{
		ft_putstr_fd("error: number of philosophers must be more than 0\n", 2);
		return (FALSE);
	}
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	if (check_overflow(philo, argv))
	{
		ft_putstr_fd("error\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
