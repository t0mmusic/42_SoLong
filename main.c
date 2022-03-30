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
#include <stdio.h>

/*	Loops until exit is found or exit is forced. Player commands are
	currently entered using scanf. */

void	loop_function(t_list *map_list, t_tile *tile)
{
	char	*input;
	char	**map;

	map = map_init(map_list);
	rectangle_check(map);
	find_pieces(map, tile);
	if (error_check(map, tile))
		return ;
	print_map(map);
	while (tile->quit)
	{
		ft_printf("Number of Moves: %i\n", tile->move_count);
		tile->move_count++;
		input = malloc(10);
		scanf("%s", input);
		if (!ft_strcmp(input, "w") || !ft_strcmp(input, "a")
			|| !ft_strcmp(input, "s") || !ft_strcmp(input, "d"))
			move_check(input, map, tile);
		if (!ft_strcmp(input, "exit"))
			tile->quit = 0;
		free(input);
		input = NULL;
	}
}

/*	Initialise map. */

int	main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_tile	*tile;
	t_list	*map_list;

	tile = tile_init();
	if (ac != 2)
	{
		ft_printf("Error\nIncorrect Number of Arguments.\n");
		return (1);
	}
	valid_input(av[1]);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	map_list = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(fd);
		ft_lstadd_back(&map_list, ft_lstnew(line));
	}
	loop_function(map_list, tile);
}
