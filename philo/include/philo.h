#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define TRUE	1
# define FALSE	0
# define ERROR	-1

typedef struct s_philo t_philo;

struct s_philo
{
	int	philo_count;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	eat_count;
};

/* Libft Functions */
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);

/* check error  */
int		args_are_valid(int argc, char **argv);

/* parsing */
int		get_number_to_struct(t_philo *philo, char **argv);



#endif