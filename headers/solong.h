/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:32:03 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/01 10:32:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include "mlx.h"

typedef struct s_coor
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_tile
{
	struct s_coor	*player;
	struct s_coor	*max;
	int				item_count;
	int				item_total;
	int				move_count;
	int				quit;
	int				exit_swap;
}	t_tile;

typedef struct s_enemy
{
	struct s_coor	*coor;
	int				direction;
	void			*next;
}	t_enemy;

typedef struct s_mlx
{
	struct s_coor	*dim;
	void			*mlx;
	void			*win;
	void			*player;
	void			*ground;
	void			*wall;
	void			*exit;
	void			*item;
	void			*enemy;
}	t_mlx;

typedef struct s_data
{
	struct s_enemy	*enemy;
	struct s_tile	*tile;
	struct s_mlx	*mlx;
	char			**map;
}	t_data;

/*	Outdated functions	*/

void	loop_function(t_list *map_list, t_tile *tile);
void	print_map(char **map);

/*	Initialisation	*/

void	collect_data(t_list *map_list, t_tile *tile);
void	initialise_map(t_tile *tile, char **map, t_mlx *mlx);
t_mlx	*init_mlx(t_tile *tile);
char	**map_init(t_list *map_list);
t_tile	*tile_init(void);

/*	Input from users	*/

void	user_input(t_data *data);
int		key_press(int key, t_data *data);

/*	Movement functions	*/

void	move_check(int input, char **map, t_tile *tile, t_mlx *mlx);
void	move_player(char **map, t_tile *tile, int x, int y);
void	print_movement(int input);

/*	Map Location Functions	*/

t_enemy	*find_pieces(char **map, t_tile *tile, t_enemy *list);
void	set_coordinates(t_tile *tile, char c, int x, int y);
void	find_map_max(char **map, t_tile *tile);

/*	Enemy Functions	*/

t_enemy	*new_enemy(int x, int y);
t_enemy	*add_enemy(t_enemy *list, t_enemy *current);
void	enemy_movement(t_enemy *enemy, t_tile *tile, char **map, t_mlx *mlx);
void	player_collision(t_enemy *enemy, t_tile *tile);

/*	Error checking	*/

void	valid_input(char *str);
void	error_check(char **map, t_tile *tile);
void	rectangle_check(char **map, t_tile *tile);

/*	Exit program	*/

void	exit_program(t_tile *tile, char **map);
void	free_mlx(t_mlx *mlx);
void	free_map(char **map);
void	free_tile(t_tile *tile);

#endif
