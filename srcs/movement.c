/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:20:55 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/25 13:27:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Updates the player position and replaces the ground where the player
	was previously standing. If the player was standing at the exit, it will
	place that image on top of the ground tile. */

void	map_update(t_mlx *mlx, t_tile *tile, int x, int y)
{
	image_put(mlx, mlx->ground, x, y);
	if (tile->exit_swap)
		image_put(mlx, mlx->exit, x, y);
	image_put(mlx, mlx->ground, tile->player->x, tile->player->y);
	image_put(mlx, mlx->player, tile->player->x, tile->player->y);
}

/*	Checks what was on the space that the player just moved to. If
	it was an exit, it will check that the collectible has been picked up.
	If it hasn't, it will save the location of the exit. If it finds a
	collectible, the collectible counter is increased. It then swaps the 
	position the player came from with '0' and the position the player moved 
	to with 'P' */

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
			tile->quit = 1;
		}
	}
	if (map[tile->player->y][tile->player->x] == 'C')
		tile->item_count++;
	map[tile->player->y][tile->player->x] = 'P';
}

/*	Checks to see if the player can move in the direction chosen. If they
	can, move_player and map_update are called to update the player's position.
	The move count will update regardless of whether the player can move or not
	because the enemies can still move on this turn. */

void	move_check(int input, char **map, t_tile *tile, t_mlx *mlx)
{
	int	x;
	int	y;

	x = tile->player->x;
	y = tile->player->y;
	if (input == UP && map[y - 1][x] != '1')
		tile->player->y--;
	if (input == LEFT && map[y][x - 1] != '1')
		tile->player->x--;
	if (input == DOWN && map[y + 1][x] != '1')
		tile->player->y++;
	if (input == RIGHT && map[y][x + 1] != '1')
		tile->player->x++;
	if (!(x == tile->player->x && y == tile->player->y))
	{
		map_update(mlx, tile, x, y);
		move_player(map, tile, x, y);
	}
	tile->move_count++;
	ft_printf("Number of Moves: %i\n", tile->move_count);
}

/*	Prints the direction of movement	*/

void	print_movement(int input)
{
	if (input == 13)
		ft_printf("Up\n");
	if (input == 0)
		ft_printf("Left\n");
	if (input == 1)
		ft_printf("Down\n");
	if (input == 2)
		ft_printf("Right\n");
}
