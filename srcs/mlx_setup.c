/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:20:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/14 16:06:38 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Lays out all of the images in the window in the same position they appear
	in the input map. It places a floor tile in every position to account for
	floor tiles that are larger than other tiles.	*/

void	initialise_map(t_tile *tile, char **map, t_mlx *mlx)
{
	int	x;
	int	y;

	x = -1;
	while (++x < tile->max->x)
	{
		y = -1;
		while (++y < tile->max->y)
		{
			mlx_put_image_to_window(mlx, mlx->win,
				mlx->ground, x * mlx->dim->x, y * mlx->dim->y);
			if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->item, x * mlx->dim->x, y * mlx->dim->y);
			if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->player, x * mlx->dim->x, y * mlx->dim->y);
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->wall, x * mlx->dim->x, y * mlx->dim->y);
			if (map[y][x] == 'E')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->exit, x * mlx->dim->x, y * mlx->dim->y);
			if (map[y][x] == 'B')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->enemy, x * mlx->dim->x, y * mlx->dim->y);
		}
	}
}

/*	Creates an mlx instance and a graphical window, then assigns 
	all of the images into pointers. The tile size is determined
	by the dimensions of the floor tiles, so that image is initialised
	first. The window size is the maximum x and y coordiates multiplied
	by the floor tile size.	*/

t_mlx	*init_mlx(t_tile *tile)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = malloc(sizeof(*mlx));
	mlx->dim = malloc(sizeof(int) * 2);
	mlx->mlx = mlx_init();
	mlx->ground = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/floor.xpm", &mlx->dim->x, &mlx->dim->y);
	mlx->win = mlx_new_window(mlx->mlx, tile->max->x * mlx->dim->x,
			tile->max->y * mlx->dim->y, "So Long!");
	mlx->player = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/player.xpm", &x, &y);
	mlx->wall = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/wall.xpm", &x, &y);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/exit.xpm", &x, &y);
	mlx->item = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/item.xpm", &x, &y);
	mlx->enemy = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/enemy.xpm", &x, &y);
	return (mlx);
}

/*	Checks to see if the key that was pressed by the user
	was valid for movement or to exit the program. If it was
	for movement, it will use move_check to see if the movement
	is possible, then it will print the direction of movement. */

int	key_press(int key, t_data *data)
{
	t_mlx	*mlx;
	t_tile	*tile;
	char	**map;

	map = data->map;
	tile = data->tile;
	mlx = data->mlx;
	tile->quit = 1;
	if (key == 13 || key == 0 || key == 1 || key == 2)
		move_check(key, map, tile, mlx);
	if (!(tile->quit) || key == 53)
	{
		free_mlx(mlx);
		free(data);
		exit_program(tile, map);
	}
	enemy_movement(data->enemy, tile, map, mlx);
	print_movement(key);
	return (0);
}

/*	Compiles all of the structures used by the key hook into one
	larger structure so that all of the data can be used in later
	functions. I really wish I could use global variables.	*/

void	collect_data(t_list *map_list, t_tile *tile)
{
	t_mlx	*mlx;
	t_data	*data;
	t_enemy	*enemy;
	char	**map;

	enemy = new_enemy(0, 0);
	map = map_init(map_list);
	rectangle_check(map, tile);
	enemy = find_pieces(map, tile, enemy);
	error_check(map, tile);
	data = malloc(sizeof(*data));
	mlx = init_mlx(tile);
	data->map = map;
	data->mlx = mlx;
	data->tile = tile;
	data->enemy = enemy;
	initialise_map(tile, map, mlx);
	user_input(data);
}

/*	Sets up the mlx loop so that the program stays open to
	recieve user inputs.	*/

void	user_input(t_data *data)
{
	int		key;

	key = mlx_key_hook(data->mlx->win, key_press, data);
	mlx_loop(data->mlx->mlx);
}
