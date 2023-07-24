NAME = libft.a
SRC = ft_bzero.c   ft_calloc.c  ft_split.c   ft_strjoin.c ft_strlen.c  ft_strncmp.c ft_strrchr.c ft_substr.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra

.SILENT:

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

all:	$(NAME) 

clean:
	rm -f *.o *.out

fclean:	clean
	rm -f *.a

re:	fclean all

