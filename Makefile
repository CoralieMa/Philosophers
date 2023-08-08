NAME	= philo

FILES	= philo \
				utils \
				mutex \
				ft_atoi \
				ft_time \
				threads \
				routine \
				initialise \
				verification_input \


SRCS	= ${addprefix SRCS/, $(addsuffix .c, $(FILES))}

OBJS	= ${SRCS:.c=.o}

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g

RM		= rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all :	${NAME}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re