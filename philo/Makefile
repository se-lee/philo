NAME = philo

SRCS =	check_error.c	\
		libft_fns.c		\
		parsing.c		\
		main.c			\

GCCF = gcc -g -Wall -Wextra -Werror #-fsanitize=address

OBJS = $(addprefix bin/, ${SRCS:.c=.o})

.PHONY :	all clean fclean re libft_

bin/%.o : 	srcs/%.c	include/philo.h
			@mkdir -p $(dir $@)
			${GCCF} -c $< -o $@ -Iinclude

all :		libft_ ${NAME}

$(NAME) :	${OBJS} include/philo.h
			${GCCF} $(OBJS) -o $(NAME)

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all
