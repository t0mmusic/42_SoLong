/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:14:34 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/26 15:14:36 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Checks what was on the space that the player just moved to. If
	it was an exit, it will check that the collectibles have been picked up.
	If not all have been collected, it will save the location of the exit. */

void	move_player(char **map, t_tile *tile, int x, int y)
{
	map[y][x] = '0';
	if (tile->exit_swap)
	{
		map[y][x] = 'E';
		tile->exit_swap = 0;
	}
	if (map[tile->player->y][tile->player->x] == 'E')
	{
		if (tile->item_count != tile->item_total)
			tile->exit_swap = 1;
		else
		{
			ft_printf("Success!\n");
			tile->quit = 0;
		}
	}
	if (map[tile->player->y][tile->player->x] == 'C')
		tile->item_count++;
	map[tile->player->y][tile->player->x] = 'P';
}

/*	Checks to see if the players movements have changed. */

void	move_check(char *input, char **map, t_tile *tile)
{
	int	x;
	int	y;

	x = tile->player->x;
	y = tile->player->y;
	if (!ft_strcmp(input, "w") && map[y - 1][x] != '1')
		tile->player->y--;
	if (!ft_strcmp(input, "a") && map[y][x - 1] != '1')
		tile->player->x--;
	if (!ft_strcmp(input, "s") && map[y + 1][x] != '1')
		tile->player->y++;
	if (!ft_strcmp(input, "d") && map[y][x + 1] != '1')
		tile->player->x++;
	if (!(x == tile->player->x && y == tile->player->y))
	{
		move_player(map, tile, x, y);
		print_map(map);
	}
}
