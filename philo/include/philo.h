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

typedef struct s_data t_data;
typedef struct s_philo t_philo;


/* every single philosopher will have this struct */
struct s_philo
{
	int				id; //"name" of each philo
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	int				eat_count;
	long			time_before_die;
	t_data			*data;
};

struct s_data
{
	int		philo_count;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eat_count;
	long	time_start;
	long	time_actual;
	int		died;
	int		ready;
	pthread_mutex_t	print_mutex;
	t_philo	*philo;
};

/* Libft Functions */
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

/* check error  */
int		args_are_valid(int argc, char **argv);
int		check_overflow(t_data *philo, char **argv);

/* init */
void	init_struct(t_data *data);
void	init_philo(t_data *data);

/* parsing */
int		get_number_to_struct(t_data *philo, char **argv);

/* time */
long	get_time_in_ms(void);

/* activity */
void	sleeping_func(t_philo *philo);
void	eating_func(t_philo *philo);
void	ft_sleep(t_data *data, int time_to_sleep);
void	print_status(t_philo *philo, char *str);
void	*philo_activities(void *arg);

#endif