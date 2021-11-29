/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:19 by selee             #+#    #+#             */
/*   Updated: 2021/11/29 10:22:16 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	int				times_eaten;
	long			time_before_die;
	pthread_mutex_t	check;
	t_data			*data;
};

struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long			time_start;
	long			time_actual;
	int				died;
	int				ready;
	int				philo_finished;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
};

/* activity */
void	wait_upto(t_data *data, int time_to_wait);
int		philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	*philo_activities(void *arg);

/* init */
int		init_struct(t_data *data);
int		init_all_philo(t_data *data);

/* Libft parsing */
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);

/* Libft print */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* parsing  */
int		args_are_positive_nbr(char **argv);
int		args_overflow(t_data *philo, char **argv);
int		parse(t_data *philo, int argc, char **argv);

/* time */
long	get_time_in_ms(void);

/* utils */
void	*malloc_protected(int size, int count);
int		print_status(t_philo *philo, char *str, int in_main);

#endif
