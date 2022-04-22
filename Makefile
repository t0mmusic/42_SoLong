NAME = solong
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders

PRINTF_A = printf/libftprintf.a

MLX_LINUX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX_FLAGS = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

RM = rm -f

SRCS = srcs/*.c

CHECKER = tester/checker.c

GET_NEXT_LINE = gnl/get_next_line.c

REMOVE_MESSAGE = echo "removing object files"
REMOVE_ARCHIVE = echo "removing archives and application"
COMPILE_PRINTF = echo "compiling printf archive..."
COMPILE_SOLONG = echo "compiling solong application"
COMPILE_COMPLETE = echo "Ready! To play the game:\n./solong maps/<map name>"

all: $(NAME)

$(NAME):
	@$(COMPILE_PRINTF)
	@$(MAKE) bonus -C ./printf >/dev/null
	@$(COMPILE_SOLONG)
	@$(CC) $(CFLAGS) $(SRCS) $(PRINTF_A) $(GET_NEXT_LINE) $(MLX_FLAGS) -D BUFFER_SIZE=100 -o $(NAME) >/dev/null
	@$(COMPILE_COMPLETE)

bonus: all

clean:
	@$(REMOVE_MESSAGE)
	@$(MAKE) clean -C ./printf >/dev/null
	@$(MAKE) clean -C ./printf/libft >/dev/null

fclean: clean
	@$(REMOVE_ARCHIVE)
	@$(MAKE) fclean -C ./printf >/dev/null
	@$(MAKE) clean -C ./printf/libft >/dev/null
	@$(RM) $(NAME) >/dev/null

re: fclean all

.PHONY: all clean fclean bonus re