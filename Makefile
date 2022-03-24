NAME = solong.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders -I . -c

MLX_LINUX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RM = rm -f

SRCS = srcs/*.c

OBJ_DEST = mv *.o srcs

CHECKER = tester/checker.c

GET_NEXT_LINE = gnl/get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	$(MAKE) bonus -C ./printf
	cp printf/libftprintf.a $(NAME)
	$(CC) $(CFLAGS) $(GET_NEXT_LINE) -D BUFFER_SIZE=100
	$(OBJ_DEST)
	ar rcs $(NAME) $(OBJS) mlx_linux/libmlx_Linux.a
	$(CC) main.c $(NAME) $(MLX_LINUX_FLAGS) -Iheaders -o solong

clean:
	$(MAKE) clean -C ./printf
	$(MAKE) clean -C ./printf/libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./printf
	$(MAKE) clean -C ./printf/libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re