SRCS = fdf.c \
			debug.c \
			file.c \
			map.c \
			utils.c \
			./gnl/get_next_line_utils.c \
			./gnl/get_next_line.c \
			map_utils.c \

OBJS = $(SRCS:.c=.o) ./libft/libft.a

MLX = ./minilibx-linux/libmlx_Linux.a

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

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean
	make all

.PHONY: all clean fclean re