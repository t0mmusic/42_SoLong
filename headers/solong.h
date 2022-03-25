#ifndef SOLONG_H
# define SOLONG_H

# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include "mlx.h"

typedef struct s_xy//change to s_coor
{
	int	x;
	int	y;
}	t_xy;

typedef struct s_coor//change to s_tile
{
	//t_xy	player;
	//t_xy	exit;
	//t_xy	item;
	//t_xy	max;
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

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*player;
	void	*ground;
	void	*wall;
	void	*exit;
	void	*item;
}	t_mlx;

typedef struct s_data
{
	struct s_coor	*tile;
	struct s_mlx	*mlx;
	char			**map;
}	t_data;


void	loop_function(char **map, t_coor *location);
void	move_check(int input, char **map, t_coor *pixel, t_mlx *mlx);
void	move_player(char **map, t_coor *pixel, int x, int y);
void	find_pieces(char **map, t_coor *location);
void	print_map(char **map, t_coor *pixel);

void	update_map(t_coor *pixel, char **map, t_mlx *mlx);
t_mlx	*init_mlx(t_coor *tile);

void	user_input(char **map, t_coor *tile);
int	key_press(int key, t_data *data);

#endif