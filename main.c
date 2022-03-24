/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:46:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/24 20:46:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Prints the map with the updated positions. This will work differently
	when graphics are added. */

void	print_map(char **map, t_coor *pixel)
{
	int	i;

	i = 0;
	while (map[i] && i <= pixel->x_max)
	{
		ft_printf("%s", map[i]);
		i++;
	}
	ft_printf("\n");
}

/*	Checks the bounds of the map to find where the player, exit and
	collectible are and sets their coordinates accordingly. This will
	need to be changed to account for multiple collectibles and multiple
	exits. */

void	find_pieces(char **map, t_coor *location)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x][y] && map[x][y] == '1')
		y++;
	location->y_max = y - 1;
	y = 0;
	x = 1;
	while (x < location->x_max)
	{
		if (map[x][y] == 'P')
		{
			location->x_player = x;
			location->y_player = y;
		}
		if (map[x][y] == 'C')
		{
			location->x_collect = x;
			location->y_collect = y;
		}
		if (map[x][y] == 'E')
		{
			location->x_exit = x;
			location->y_exit = y;
		}
		if (y < location->y_max)
			y++;
		else
		{
			y = 1;
			x++;
		}
	}
}

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

void	move_check(char *input, char **map, t_coor *pixel)
{
	int	x;
	int	y;

	x = pixel->x_player;
	y = pixel->y_player;
	if (!ft_strcmp(input, "w") && map[x - 1][y] != '1')
		pixel->x_player--;
	if (!ft_strcmp(input, "a") && map[x][y - 1] != '1')
		pixel->y_player--;
	if (!ft_strcmp(input, "s") && map[x + 1][y] != '1')
		pixel->x_player++;
	if (!ft_strcmp(input, "d") && map[x][y + 1] != '1')
		pixel->y_player++;
	ft_printf("x: %i\ny: %i\n", pixel->x_player, pixel->y_player);
	if (!(x == pixel->x_player && y == pixel->y_player))
	{
		move_player(map, pixel, x, y);
		print_map(map, pixel);
	}
}

/*	Loops until exit is found or exit is forced. Player commands are
	currently entered using scanf. */
void	loop_function(char **map, t_coor *location)
{
	char	*input;

	find_pieces(map, location);
	location->exit = 1;
	location->collect = 0;
	location->exit_swap = 0;
	while (location->exit)
	{
		input = malloc(10);
		scanf("%s", input);
		ft_printf("input: %s\n", input);
		if (!ft_strcmp(input, "w") || !ft_strcmp(input, "a")
			|| !ft_strcmp(input, "s") || !ft_strcmp(input, "d"))
			move_check(input, map, location);
		if (!ft_strcmp(input, "exit"))
			location->exit = 0;
		free(input);
		input = NULL;
	}
}

/*	Initialise map. Need to add check that file entered is .ber.
	Error checking needed for at least one player, collectible and
	exit.  */

int	main(int ac, char **av)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;
	t_coor	*location;

	location = malloc(sizeof(*location));
	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	map = malloc(sizeof(*map));
	i = 0;
	while (line)
	{
		map[i] = ft_strdup(line);
		ft_printf("%s", map[i]);
		line = get_next_line(fd);
		i++;
	}
	location->x_max = i - 1;
	ft_printf("\n");
	loop_function(map, location);
}
