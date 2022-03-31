#include "solong.h"

/*	Checks what was on the space that the player just moved to. If
	it was an exit, it will check that the collectible has been picked up.
	If it hasn't, it will save the location of the exit. If it finds the
	collectible, the collectible flag is set. It then swaps the position
	the player came from with '0' and the position the player moved 
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
			tile->quit = 0;
		}
	}
	if (map[tile->player->y][tile->player->x] == 'C')
		tile->item_count++;
	map[tile->player->y][tile->player->x] = 'P';
}

/*	Checks to see if the players movements have changed. */

void	move_check(int input, char **map, t_tile *tile, t_mlx *mlx)
{
	int	x;
	int	y;

	x = tile->player->x;
	y = tile->player->y;
	if (input == 13 && map[y - 1][x] != '1')
	{
		tile->player->y--;
	}
	if (input == 0 && map[y][x - 1] != '1')
		tile->player->x--;
	if (input == 1 && map[y + 1][x] != '1')
		tile->player->y++;
	if (input == 2 && map[y][x + 1] != '1')
		tile->player->x++;
	if (!(x == tile->player->x && y == tile->player->y))
	{
		tile->move_count++;
		ft_printf("Number of Moves: %i\n", tile->move_count);
		move_player(map, tile, x, y);
		update_map(tile, map, mlx);
	}
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