# # executable name
# NAME = cub3d

# # flags
# CC = gcc
# # CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

# # directories
# OBJDIR = ./obj/
# SRCDIR = ./src/

# # source files
# SRCFILES = main.c graphics.c map.c my_mlx.c rays.c player.c input.c walls.c release.c draw.c rays_utils.c textures.c
# # object files
# OBJFILES = $(SRCFILES:.c=.o)

# # library paths
# LIBFT = ./inc/libft
# FT_PRINTF = ./inc/ft_printf
# MLX = ./inc/mlx

# # files path
# SRC = $(addprefix $(SRCDIR), $(SRCFILES))
# OBJ = $(addprefix $(OBJDIR), $(OBJFILES))

# # silence output 
# .SILENT:

# # all rule 
# all: $(OBJDIR) $(NAME)

# # compile executable and libraries
# $(NAME):	$(OBJ)
# 	$(MAKE) -C $(LIBFT)
# 	$(MAKE) -C $(MLX) 2>/dev/null
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a $(MLX)/libmlx.a -framework OpenGL -framework AppKit -o $@
# 	echo "Compilation done successfully!"

# # compile objects
# $(OBJDIR)%.o: $(SRCDIR)%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# # create object directory
# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# # clean rule
# clean:
# 	rm -rf $(OBJDIR)
# 	$(MAKE) -C $(LIBFT) clean
# 	$(MAKE) -C $(MLX) clean

# # fclean rule
# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) -C $(LIBFT) fclean

# # make re rule 
# re: fclean all



# NAME = cub3D

# SRCS =	 src/main.c src/graphics.c src/map.c src/my_mlx.c src/rays.c src/player.c src/input.c src/walls.c src/release.c src/draw.c src/rays_utils.c src/textures.c

# OS := $(shell uname)

# OBJS = $(SRCS:.c=.o)

# CC = cc

# CFLAGS = -Wall -Werror -Wextra -D $(OS) -Ofast -march=native

# RM = /bin/rm

# # LIBS
# LIBFT = inc/libft


# ifeq ($(OS), Linux)
# 	MLX = inc/mlx_linux
# else
# 	MLX = inc/mlx
# endif

# LINKS = -lm -L $(MLX) -L inc/libft -lft

# ifeq ($(OS), Linux)
# 	LINKS += -L/usr/lib -lmlx -lXext -lX11
# else
# 	LINKS += -lmlx -framework OpenGL -framework AppKit
# endif

# HEADER	= -Iinclude -I/usr/include -I$(MLX) -I$(LIBFT)

# .c.o:
# 	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} $(HEADER)

# all : $(NAME)

# $(NAME): $(OBJS)
# 	make -C $(MLX)
# 	make -C $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

# clean:
# 	(cd $(LIBFT) && make clean)
# 	(cd $(MLX) && make clean)
# 	$(RM) -f $(OBJS)

# fclean: clean
# 	(cd $(LIBFT) && make fclean)
# 	$(RM) -f $(NAME)

# re: fclean all

# re2:
# 	(cd $(LIBFT) && make fclean)
# 	$(RM) -f $(OBJS)
# 	make all

# .PHONY: all clean fclean re


NAME	=	cub3D

SRCS	=	src/main.c src/graphics.c src/map.c src/my_mlx.c src/rays.c src/player.c src/input.c src/walls.c src/release.c src/draw.c src/rays_utils.c src/textures.c

OBJS	=	${SRCS:.c=.o}

HEADER	=	include

LIBFT	=	inc/libft/libft.a

# CC		=	gcc -fsanitize=address,undefined,float-divide-by-zero -g3
CC		=	cc -g3

OS		:=	$(shell uname)

ifeq ($(OS),Linux)
	MLX			=	libmlx.a
	MLX_DIR		=	inc/mlx_linux
	CFLAGS		=	-Wall -Werror -Wextra -I${HEADER} -I/usr/include -I ${MLX_DIR} -O3 -Ofast
	MLX_FLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lm -lXext -lX11 -lz
else
	MLX			=	libmlx.dylib
	MLX_DIR		=	mlx
	CFLAGS		=	-Wall -Werror -Wextra -I ${HEADER} -I ${MLX_DIR} -Ofast
	MLX_FLAGS	=	-L. -lmlx -framework OpenGL -framework AppKit
endif

${NAME}:	${LIBFT} ${MLX} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX_FLAGS} -o ${NAME} 

${LIBFT}:
			${MAKE} -C inc/libft

${MLX}:
			${MAKE} -C ${MLX_DIR}
			mv ${MLX_DIR}/${MLX} .

all:		${NAME}

clean:
			rm -f ${OBJS}
			rm -f ${MLX}
			${MAKE} -C inc/libft clean
			# ${MAKE} -C ${MLX_DIR} clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C inc/libft fclean

bonus:		all

re:			fclean all

.PHONY:		all clean fclean rea