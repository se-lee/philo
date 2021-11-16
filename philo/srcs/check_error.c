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

int		check_overflow(t_philo *philo, char **argv)
{
	char	*temp;

	temp = 
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