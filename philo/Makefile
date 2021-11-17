NAME = philo

SRCS =	activity.c		\
		init.c			\
		libft_fns.c		\
		main.c			\
		parsing.c		\
		time.c			\

GCCF = gcc -g -fsanitize=address #-Wall -Wextra -Werror 

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
