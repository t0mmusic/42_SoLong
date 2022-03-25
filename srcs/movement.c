#include "solong.h"

/*	Checks what was on the space that the player just moved to. If
	it was an exit, it will check that the collectible has been picked up.
	If it hasn't, it will save the location of the exit. If it finds the
	collectible, the collectible flag is set. It then swaps the position
	the player came from with '0' and the position the player moved 
	to with 'P' */

void	move_player(char **map, t_coor *pixel, int x, int y)
{
	map[x][y] = '0';
	if (pixel->exit_swap)
	{
		map[x][y] = 'E';
		pixel->exit_swap = 0;
	}
	if (!pixel->collect && map[pixel->x_player][pixel->y_player] == 'E')
		pixel->exit_swap = 1;
	if (pixel->collect && map[pixel->x_player][pixel->y_player] == 'E')
	{
		ft_printf("Success!\n");
		pixel->exit = 0;
	}
	if (map[pixel->x_player][pixel->y_player] == 'C')
		pixel->collect = 1; 
	map[pixel->x_player][pixel->y_player] = 'P';
} //make a pixel collect function that returns 1 if all collectibles are found

/*	Checks to see if the players movements have changed. */

void	move_check(int input, char **map, t_coor *pixel, t_mlx *mlx)
{
	int	x;
	int	y;

	x = pixel->x_player;
	y = pixel->y_player;
	if (input == 13 && map[x - 1][y] != '1')
	{
		pixel->x_player--;
	}
	if (input == 0 && map[x][y - 1] != '1')
		pixel->y_player--;
	if (input == 1 && map[x + 1][y] != '1')
		pixel->x_player++;
	if (input == 2 && map[x][y + 1] != '1')
		pixel->y_player++;
	if (!(x == pixel->x_player && y == pixel->y_player))
	{
		move_player(map, pixel, x, y);
		//print_map(map, pixel);
		update_map(pixel, map, mlx);
	}
}