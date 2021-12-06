NAME = philo

SRCS =	activity.c			\
		init.c				\
		libft_parsing.c		\
		libft_print.c		\
		main.c				\
		parsing.c			\
		utils.c				\

GCCF = gcc -g -Wall -Wextra -Werror

OBJS = $(addprefix bin/, ${SRCS:.c=.o})

.PHONY :	all clean fclean re libft_

bin/%.o : 	srcs/%.c	include/philo.h
			@mkdir -p $(dir $@)
			${GCCF} -c $< -o $@ -Iinclude -pthread

all :		libft_ ${NAME}

$(NAME) :	${OBJS} include/philo.h
			${GCCF} $(OBJS) -o $(NAME) -pthread -lpthread

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all
