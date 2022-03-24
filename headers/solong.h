#ifndef SOLONG_H
# define SOLONG_H

# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include "mlx.h"
# include <stdio.h>

typedef struct s_coor
{
	int		x_player;
	int		y_player;
	int		x_exit;
	int		y_exit;
	int		x_collect;
	int		y_collect;
	int		x_max;
	int		y_max;
	int		collect;
	int		exit;
	int		exit_swap;
}	t_coor;

void	loop_function(char **map, t_coor *location);
void	move_check(char *input, char **map, t_coor *pixel);
void	move_player(char **map, t_coor *pixel, int x, int y);
void	find_pieces(char **map, t_coor *location);
void	print_map(char **map, t_coor *pixel);

#endif