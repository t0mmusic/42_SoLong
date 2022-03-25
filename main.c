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
	{
		y++;
	}
	location->y_max = y - 1;
	y = 1;
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
		if (y < location->y_max - 1)
			y++;
		else
		{
			y = 1;
			x++;
		}
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
	map = malloc(sizeof(*map) * 10);//need to figure out number of lines
	i = 0;
	while (line)
	{
		map[i] = ft_strdup(line);
		//ft_printf("%s", map[i]);
		line = get_next_line(fd);
		i++;
	}
	location->x_max = i - 1;
	ft_printf("\n");
	//loop_function(map, location);
	user_input(map, location);
}
