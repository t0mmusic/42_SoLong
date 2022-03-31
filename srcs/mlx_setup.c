/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:20:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/31 16:20:48 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Lays out all of the images in the window in the same position they appear
	in the input map.	*/

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
				mlx->ground, x * 16, y * 16);
			if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->item, x * 16 + 4, y * 16);
			if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->player, x * 16, y * 16);
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->wall, x * 16, y * 16);
			if (map[y][x] == 'E')
				mlx_put_image_to_window(mlx, mlx->win,
					mlx->exit, x * 16 + 2, y * 16);
		}
	}
}

/*	Creates an mlx instance and a graphical window, then assigns 
	all of the images into pointers. */

t_mlx	*init_mlx(t_tile *tile)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = malloc(sizeof(*mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx,
			tile->max->x * 16, tile->max->y * 16, "So Long!");
	mlx->player = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/player.xpm", &x, &y);
	mlx->ground = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/floor.xpm", &x, &y);
	mlx->wall = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/wall.xpm", &x, &y);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/exit.xpm", &x, &y);
	mlx->item = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/item.xpm", &x, &y);
	return (mlx);
}

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
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	print_movement(key);
	return (0);
}

void	user_input(t_list *map_list, t_tile *tile)
{
	int		key;
	t_mlx	*mlx;
	t_data	*data;
	char	**map;

	map = map_init(map_list);
	rectangle_check(map);
	find_pieces(map, tile);
	error_check(map, tile);
	data = malloc(sizeof(*data));
	mlx = init_mlx(tile);
	data->map = map;
	data->mlx = mlx;
	data->tile = tile;
	initialise_map(tile, map, mlx);
	key = mlx_key_hook(mlx->win, key_press, data);
	mlx_loop(mlx->mlx);
}
