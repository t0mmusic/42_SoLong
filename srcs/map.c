/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:14:27 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/26 15:14:28 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Prints the map with the updated positions. This was used to display the map
	in the terminal but is not included in the final project. */

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
	ft_printf("\n");
}

/*	Finds the x and y boundaries of the map. */

void	find_map_max(char **map, t_tile *tile)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	tile->max->x = i - 2;
	i = 0;
	while (map[i])
		i++;
	tile->max->y = i;
}

/*	Finds the location of the player and the total number of
	collectables. */

void	set_coordinates(t_tile *tile, char c, int x, int y)
{
	if (c == 'P')
	{
		tile->player->x = x;
		tile->player->y = y;
	}
	if (c == 'C')
		tile->item_total++;
}

/*	Checks the bounds of the map to find where the player and
	collectibles are and sets their coordinates accordingly.	*/

t_enemy	*find_pieces(char **map, t_tile *tile, t_enemy *list)
{
	int		x;
	int		y;

	y = 1;
	x = 1;
	find_map_max(map, tile);
	while (y < tile->max->y)
	{
		if (map[y][x] == 'P' || map[y][x] == 'C')
			set_coordinates(tile, map[y][x], x, y);
		if (map[y][x] == 'B')
		{
			list = add_enemy(list, new_enemy(x, y));
		}
		if (x < tile->max->x)
			x++;
		else
		{
			x = 1;
			y++;
		}
	}
	return (list);
}
