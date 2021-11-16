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

int		check_overflow(t_data *philo, char **argv)
{
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