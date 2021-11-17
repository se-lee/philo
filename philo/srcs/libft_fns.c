#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && fd > 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	__int128_t	nbr;
	int			sign;
	int			i;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (sign == 1 && nbr > LONG_MAX)
			return ((int)LONG_MAX);
		if (sign == -1 && - nbr < LONG_MIN)
			return ((int)LONG_MIN);
		i++;
	}
	return (nbr * sign);
}

static int	ft_len_nbr(int n)
{
	unsigned int	i;
	long long int	nbr;

	nbr = (long long int)n;
	i = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	int				len;
	long long int	nbr;

	nbr = (long long int)n;
	len = ft_len_nbr(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	i = len - 1;
	while (nbr >= 10)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	str[i] = nbr % 10 + '0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}