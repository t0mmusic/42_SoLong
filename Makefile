NAME = solong
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders


PRINTF_A = printf/libftprintf.a

OBJ_DEST = objects
HEADER_DEST = headers
ARCHIVE_DEST = archives

PRINTF = $(OBJ_DEST) $(HEADER_DEST) $(ARCHIVE_DEST)

OBJS = $(SRCS:srcs/%.c=objects/%.o)

GNL = gnl

MLX_LINUX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX_FLAGS = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

RM = rm -f

SRCS = srcs/count.c srcs/enemy.c srcs/error.c srcs/exit.c srcs/images.c \
		srcs/loop.c srcs/map_error.c srcs/map.c srcs/movement.c srcs/initilise.c

CHECKER = tester/checker.c

GET_NEXT_LINE = gnl/get_next_line.c

REMOVE_MESSAGE = echo "removing object files"
REMOVE_ARCHIVE = echo "removing archives and application"
COMPILE_PRINTF = echo "compiling printf archive..."
COMPILE_SOLONG = echo "compiling solong application"
COMPILE_COMPLETE = echo "Ready! To play the game:\n./solong maps/<map name>"

all: $(NAME)

$(NAME): $(GNL) $(PRINTF) $(OBJS)
	@$(COMPILE_SOLONG)
	@$(CC) $(CFLAGS) objects/* $(MLX_LINUX_FLAGS) $(GET_NEXT_LINE) -D BUFFER_SIZE=100 -o $(NAME) >/dev/null
	@$(COMPILE_COMPLETE)

bonus: all

$(GNL):
	if [ ! -d "gnl/" ]; then\
		printf "get_next_line dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		git clone https://github.com/t0mmusic/get_next_line.git gnl; \
	fi

$(PRINTF):
	@$(COMPILE_PRINTF)
	@if [ ! -d "printf/" ]; then\
		printf "printf dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/t0mmusic/ft_printf.git printf; \
	fi
	@$(MAKE) bonus -C ./printf >/dev/null
	@cp -r printf/$(ARCHIVE_DEST) $(ARCHIVE_DEST)
	@cp -r printf/$(OBJ_DEST) $(OBJ_DEST)
	@cp -r printf/$(HEADER_DEST)/. $(HEADER_DEST)

objects/%.o: srcs/%.c
	@$(CC) $(CFLAGS) $(MLX_LINUX_FLAGS) -c $< -o $@

clean:
	@$(REMOVE_MESSAGE)
	@$(MAKE) clean -C ./printf >/dev/null
	@$(MAKE) clean -C ./printf/libft >/dev/null
	rm -rf $(OBJ_DEST) $(ARCHIVE_DEST)

fclean: clean
	@$(REMOVE_ARCHIVE)
	@$(MAKE) fclean -C ./printf >/dev/null
	@$(MAKE) clean -C ./printf/libft >/dev/null
	@$(RM) $(NAME) >/dev/null

re: fclean all

.PHONY: all clean fclean bonus re