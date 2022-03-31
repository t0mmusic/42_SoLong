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
	tile = tile_init();
	valid_input(av[1]);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	map_list = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(fd);
		ft_lstadd_back(&map_list, ft_lstnew(line));
	}
	user_input(map_list, tile);
}
