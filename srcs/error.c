/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:14:04 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/26 15:14:08 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Checks the top and bottom borders of the map to make sure they
	are completely solid.	*/

int	top_bottom_check(char **map, t_tile *tile)
{
	int	x;
	int	y;

	y = 0;
	while (1)
	{
		x = 0;
		while (map[y][x] && x < tile->max->x)
		{
			if (map[y][x] != '1')
			{
				return (1);
			}
			x++;
		}
		if (y == 0)
			y = tile->max->y - 1;
		else
			break ;
	}
	return (0);
}

/*	Checks the left and right borders of the map to make sure they
	are completely solid.	*/

int	side_check(char **map, t_tile *tile)
{
	int	y;
	int	x;

	x = 0;
	while (1)
	{
		y = 0;
		while (y < tile->max->y && map[y][x])
		{
			if (map[y][x] != '1')
			{
				return (1);
			}
			y++;
		}
		if (x == 0)
			x = tile->max->x - 1;
		else
			break ;
	}
	return (0);
}

/*	Checks to make sure there is exactly one 'P' somewhere
	on the map. */

int	player_check(char **map, t_tile *tile)
{
	int	x;
	int	y;
	int	player_count;

	y = 1;
	player_count = 0;
	while (y < tile->max->y)
	{
		x = 1;
		while (x < tile->max->x)
		{
			if (map[y][x] == 'P')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (1);
	return (0);
}

/*	Checks to make sure there is at least one exit on the
	map. */

int	tile_check(char **map, t_tile *tile, char c)
{
	int	x;
	int	y;
	int	count;

	y = 1;
	count = 0;
	while (y < tile->max->y)
	{
		x = 1;
		while (x < tile->max->x)
		{
			if (map[y][x] == c)
			count++;
			x++;
		}
		y++;
	}
	if (!count)
		return (1);
	return (0);
}

/*	Checks if there is an error with the input map and prints
	an error message.	*/

void	error_check(char **map, t_tile *tile, t_enemy *enemy)
{
	int	error;

	error = 0;
	error += top_bottom_check(map, tile);
	error += side_check(map, tile);
	if (error)
	{
		ft_printf("Error\nMap Border Must Be Solid.\n");
		exit_program(tile, map, enemy);
	}
	error += player_check(map, tile);
	if (error)
	{
		ft_printf("Error\nMap Must Contain Exactly One Player.\n");
		exit_program(tile, map, enemy);
	}
	error += tile_check(map, tile, 'E');
	error += tile_check(map, tile, 'C');
	if (error)
	{
		ft_printf("Error\nMap Must Contain At Least");
		ft_printf(" One Collectable And One Exit.\n");
		exit_program(tile, map, enemy);
	}
}
