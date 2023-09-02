SRCS = ft_bzero.c ft_calloc.c ft_split.c ft_strlen.c \
		 ft_strncmp.c ft_strrchr.c ft_substr.c ft_strfunc.c \
		 get_next_line.c get_next_line_utils.c ft_list.c \

OBJS = ${SRCS:.c=.o}

NAME = libft.a

all: ${NAME}

${NAME}: ${OBJS}
	@ar -rcs ${NAME} ${OBJS}
	@make clean

%.o: %.c
	@gcc -Wall -Werror -Wextra -c $< -o $@

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all
