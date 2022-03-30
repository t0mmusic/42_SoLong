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

/*	Main functions	*/
void	loop_function(t_list *map_list, t_tile *tile);

/*	Initilisation functions	*/
char	**map_init(t_list *map_list);
t_tile	*tile_init(void);

/*	Movement functions	*/
void	move_check(char *input, char **map, t_tile *tile);
void	move_player(char **map, t_tile *tile, int x, int y);

/*	Map Location Functions	*/
void	find_pieces(char **map, t_tile *tile);
void	set_coordinates(t_tile *tile, char c, int x, int y);
void	find_map_max(char **map, t_tile *tile);

/*	Display functions	*/
void	print_map(char **map);

/*	Error functions	*/
int		error_check(char **map, t_tile *tile);
void	valid_input(char *str);
void	rectangle_check(char **map);

#endif