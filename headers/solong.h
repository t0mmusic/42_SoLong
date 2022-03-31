#ifndef SOLONG_H
# define SOLONG_H

# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include "mlx.h"

typedef	struct	s_coor
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_tile
{
	struct s_coor	*player;
	struct s_coor	*max;
	int		item_count;
	int		item_total;
	int		move_count;
	int		quit;
	int		exit_swap;
}	t_tile;

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
	struct s_tile	*tile;
	struct s_mlx	*mlx;
	char			**map;
}	t_data;

void	loop_function(t_list *map_list, t_tile *tile);
void	print_map(char **map);

void	update_map(t_tile *tile, char **map, t_mlx *mlx);
t_mlx	*init_mlx(t_tile *tile);

void	user_input(t_list *map_list, t_tile *tile);
int	key_press(int key, t_data *data);

/*	Movement functions	*/
void	move_check(int input, char **map, t_tile *tile, t_mlx *mlx);
void	move_player(char **map, t_tile *tile, int x, int y);
void	print_movement(int input);

/*	Map Location Functions	*/
void	find_pieces(char **map, t_tile *tile);
void	set_coordinates(t_tile *tile, char c, int x, int y);
void	find_map_max(char **map, t_tile *tile);

char	**map_init(t_list *map_list);
t_tile	*tile_init(void);
void	valid_input(char *str);

void	error_check(char **map, t_tile *tile);
void	rectangle_check(char **map);

#endif