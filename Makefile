.DELETE_ON_ERROR:
.SILENT:

COLOR_RESET = \033[0m
COLOR_GREEN = \033[32m

NAME:= philo

BUILD_DIR:= build
SRCS_DIR:= srcs
INC_DIR:= includes

SRCS_PHILO:= philo \
				verification_input \
				ft_atoi \
				threads \
				routine \
				initialise

SRCS:=	${addprefix ${SRCS_DIR}/, ${addsuffix .c, ${SRCS_PHILO}}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

CFLAGS:= -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wshadow -Wdouble-promotion -Wundef -fno-common -Wconversion -g3 -O3

SANITIZE:= -fsanitize=address -g3 -O3 -fno-omit-frame-pointer

CPPFLAGS:= ${addprefix -I,${INC_DIR}} -MMD -MP

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} ${SANITIZE} -o $@
	echo "$(COLOR_GREEN)Compilation completed.$(COLOR_RESET)"

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) ${CFLAGS} ${SANITIZE} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}
	echo "$(COLOR_GREEN)objects cleaned.$(COLOR_RESET)"

fclean: clean
	${RM} ${NAME}
	echo "$(COLOR_GREEN)executables cleaned.$(COLOR_RESET)"

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}