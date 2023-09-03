# executable name
NAME = cub3d

# flags
CC = gcc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

# directories
OBJDIR = ./obj/
SRCDIR = ./src/

# source files
SRCFILES = main.c graphics.c map.c my_mlx.c rays.c player.c input.c \
			walls.c release.c draw.c rays_utils.c textures.c \
			parse.c check.c utils.c info.c \
# object files
OBJFILES = $(SRCFILES:.c=.o)

# library paths
LIBFT = ./inc/libft
FT_PRINTF = ./inc/ft_printf
MLX = ./inc/mlx

# files path
SRC = $(addprefix $(SRCDIR), $(SRCFILES))
OBJ = $(addprefix $(OBJDIR), $(OBJFILES))

# silence output 
.SILENT:

# all rule 
all: $(OBJDIR) $(NAME)

# compile executable and libraries
$(NAME):	$(OBJ)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MLX) 2>/dev/null
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a $(MLX)/libmlx.a -framework OpenGL -framework AppKit -o $@
	printf "\x1B[32m$(NAME) ready\x1B[0m\n";

# compile objects
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# clean rule
clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MLX) clean

# fclean rule
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

# make re rule 
re: fclean all
