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

	tile = malloc(sizeof(*tile) + sizeof(int) * 7 + sizeof(t_coor));
	tile->player = malloc(sizeof(int) * 2);
	tile->max_x = 0;
	tile->max_y = 0;
	tile->quit = 0;
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
	while (++y < tile->max_y)
	{
		x = -1;
		while (++x < tile->max_x)
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
	image_put(mlx, mlx->ins, 5, y);
}

/*	Compiles all of the structures used by the key hook into one
	larger structure so that all of the data can be used in later
	functions. I really wish I could use global variables.	*/

void	collect_data(t_list *map_list, t_tile *tile)
{
	t_mlx	*mlx;
	t_data	*data;
	t_enemy	*enemy;
	t_num	*num;
	char	**map;

	num = NULL;
	enemy = new_enemy(0, 0);
	map = map_init(map_list);
	rectangle_check(map, tile, enemy);
	enemy = find_pieces(map, tile, enemy);
	error_check(map, tile, enemy);
	data = malloc(sizeof(*data) + sizeof(*mlx));
	mlx = init_mlx(tile);
	num = get_numbers(mlx, num);
	image_put(mlx, num->zero, 0, tile->max_y);
	data->num = num;
	data->map = map;
	data->mlx = mlx;
	data->tile = tile;
	data->enemy = enemy;
	initialise_map(tile, map, mlx);
	user_input(data);
}

/*	Performs a basic check to see if the correct number
	of arguments has been input and that a valid file extension
	was used, then imports the map into a linked list.	*/

int	main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_tile	*tile;
	t_list	*map_list;

	if (ac != 2)
	{
		ft_printf("Error\nIncorrect Number of Arguments.\n");
		return (1);
	}
	valid_input(av[1]);
	tile = tile_init();
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	map_list = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(fd);
		ft_lstadd_back(&map_list, ft_lstnew(line));
	}
	collect_data(map_list, tile);
	return (0);
}
