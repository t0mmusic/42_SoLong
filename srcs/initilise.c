/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:14:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/26 15:14:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Converts the map list into a grid so that
	we can use x and y coordinates.	*/

char	**map_init(t_list *map_list)
{
	char	**map;
	int		size;
	int		i;

	size = ft_lstsize(map_list);
	map = malloc(sizeof(*map) * size + 1);
	i = 0;
	while (map_list->next)
	{
		map[i] = map_list->content;
		map_list = map_list->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

/*	Sets the initial counts for tile positions and
	allocates pointers.	*/

t_tile	*tile_init(void)
{
	t_tile	*tile;

	tile = malloc(sizeof(*tile) * 7);
	tile->player = malloc(sizeof(int) * 2);
	tile->max = malloc(sizeof(int) * 2);
	tile->quit = 1;
	tile->item_count = 0;
	tile->item_total = 0;
	tile->move_count = 0;
	tile->exit_swap = 0;
	return (tile);
}

/*	Lays out all of the images in the window in the same position they appear
	in the input map. It places a floor tile in every position to account for
	floor tiles that are larger than other tiles.	*/

void	initialise_map(t_tile *tile, char **map, t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < tile->max->y)
	{
		x = -1;
		while (++x < tile->max->x)
		{
			image_put(mlx, mlx->ground, x, y);
			if (map[y][x] == 'C')
				image_put(mlx, mlx->item, x, y);
			if (map[y][x] == 'P')
				image_put(mlx, mlx->player, x, y);
			if (map[y][x] == '1')
				image_put(mlx, mlx->wall, x, y);
			if (map[y][x] == 'E')
				image_put(mlx, mlx->exit, x, y);
			if (map[y][x] == 'B')
				image_put(mlx, mlx->enemy, x, y);
		}
	}
	image_put(mlx, mlx->ins, 0, y);
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
			(tile->max->y * mlx->dim->y) + 50, "So Long!");
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
	mlx->ins = mlx_xpm_file_to_image(mlx->mlx,
			"game_images/instructions.xpm", &x, &y);
	return (mlx);
}

t_num	*get_numbers(t_mlx *mlx, t_num *num)
{
	int		x;
	int		y;

	num = malloc(sizeof(*num));
	num->zero = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/zero.xpm", &x, &y);
	num->one = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/one.xpm", &x, &y);
	num->two = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/two.xpm", &x, &y);
	num->three = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/three.xpm", &x, &y);
	num->four = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/four.xpm", &x, &y);
	num->five = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/five.xpm", &x, &y);
	num->six = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/six.xpm", &x, &y);
	num->seven = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/seven.xpm", &x, &y);
	num->eight = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/eight.xpm", &x, &y);
	num->nine = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/nine.xpm", &x, &y);
	return (num);
}
