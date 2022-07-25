NAME = solong
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders


PRINTF_A = archives/libftprintf.a

OBJ_DEST = objects
HEADER_DEST = headers
ARCHIVE_DEST = archives

PRINTF = $(OBJ_DEST) $(HEADER_DEST) $(ARCHIVE_DEST)

OBJS = $(SRCS:srcs/%.c=objects/%.o)

GNL = gnl

MLX = headers/mlx.h

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
MLX_FLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx -lXext -lX11 -lm -lz
else
MLX_FLAGS = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

RM = rm -f

SRCS = srcs/count.c srcs/enemy.c srcs/error.c srcs/exit.c srcs/images.c \
		srcs/loop.c srcs/map_error.c srcs/map.c srcs/movement.c srcs/initilise.c

CHECKER = tester/checker.c

GET_NEXT_LINE = gnl/get_next_line.c -D BUFFER_SIZE=100

REMOVE_MESSAGE = echo "removing object files"
REMOVE_ARCHIVE = echo "removing archives and application"
COMPILE_PRINTF = echo "compiling printf archive..."
COMPILE_SOLONG = echo "compiling solong application"
COMPILE_COMPLETE = echo "Ready! To play the game:\n./solong maps/<map name>"

all: $(NAME)

$(NAME): $(GNL) $(PRINTF) $(MLX) $(OBJS)
	@if [ $(MLX) ]; then \
	$(COMPILE_SOLONG); \
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF_A) $(MLX_FLAGS) $(GET_NEXT_LINE) -o $(NAME) >/dev/null; \
	$(COMPILE_COMPLETE); \
	fi

bonus: all

$(GNL):
	@if [ ! -d "gnl/" ]; then\
		printf "get_next_line dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/t0mmusic/get_next_line.git gnl; \
	fi
	@cp -r gnl/get_next_line.h $(HEADER_DEST)

$(PRINTF):
	@$(COMPILE_PRINTF)
	@if [ ! -d "printf/" ]; then\
		printf "printf dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/t0mmusic/ft_printf.git printf; \
	fi
	@$(MAKE) bonus -C ./printf --no-print-directory
	@cp -r printf/$(ARCHIVE_DEST) $(ARCHIVE_DEST)
	@cp -r printf/$(OBJ_DEST) $(OBJ_DEST)
	@cp -r printf/$(HEADER_DEST)/. $(HEADER_DEST)

$(MLX):
	@if [ $(UNAME) != Linux ]; then \
		printf "MacOS mlx repository must be downloaded separately.\n";\
	fi
	@if [ ! -d "mlx/" ]; then\
		printf "mlx dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/42Paris/minilibx-linux.git mlx; \
		cd mlx && bash configure;\
		cd .. && cp -r mlx/mlx.h $(HEADER_DEST); \
	fi

objects/%.o: srcs/%.c
	@if [ $(MLX) ]; then \
	$(CC) $(CFLAGS) $(MLX_LINUX_FLAGS) -c $< -o $@; \
	printf "Linked source: %s into object: %s\n" $< $@; \
	fi

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