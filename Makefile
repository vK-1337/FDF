SRCS = fdf.c \
			file.c \
			map_src/map.c \
			map_src/map_two.c \
			map_src/map_three.c \
			map_src/map_four.c \
			map_src/map_rotations.c \
			utils.c \
			./gnl/get_next_line_utils.c \
			./gnl/get_next_line.c \
			rotations.c \
			draw_utils.c \
			draw.c \
			cast.c \
			center.c \
			mouse.c \
			arrow_moves.c \
			zoom.c \
			keys.c \
			hooks.c \
			free.c \
			projections.c \
			mouse_moves.c \
			berserk.c \

OBJS = $(SRCS:.c=.o) ./libft/libft.a

MLX = ./minilibx-linux/libmlx_Linux.a

MLX_A = ./minilibx-linux/libmlx.a

NAME = fdf

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -L./libft -lft

# colors
GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -lXext -lX11 -lm -lz -o $(NAME) $(MLX)
	@echo "	 			+---------------------+\n \
					|  $(YELLOW)     FDF $(GREEN)[OK]$(NC)      |\n \
					+---------------------+"

$(LIBFT):
	make -C ./libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(MLX) $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(MLX) $(MLX_A)
	$(MAKE) -C ./libft fclean

re: fclean
	make all

minilibx-linux:
	git clone https://github.com/42Paris/minilibx-linux.git $@

$(MLX): minilibx-linux
								cd minilibx-linux && make

.PHONY: all clean fclean re