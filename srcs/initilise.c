/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:14:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/26 15:14:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Converts the map list into a grid so that
	we can use x and y coordinates.	*/

char	**map_init(t_list *map_list)
{
	char	**map;
	int		size;
	int		i;

	size = ft_lstsize(map_list);
	map = malloc(sizeof(*map) * size + 1);
	i = 0;
	while (map_list->next)
	{
		map[i] = map_list->content;
		map_list = map_list->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

/*	Sets the initial counts for tile positions and
	allocates pointers.	*/

t_tile	*tile_init(void)
{
	t_tile	*tile;

	tile = malloc(sizeof(*tile) * 7);
	tile->player = malloc(sizeof(int) * 2);
	tile->max = malloc(sizeof(int) * 2);
	tile->quit = 1;
	tile->item_count = 0;
	tile->item_total = 0;
	tile->move_count = 0;
	tile->exit_swap = 0;
	return (tile);
}

/*	Checks that map is rectangular. */

void	rectangle_check(char **map)
{
	int		i;
	size_t	len;

	i = 0;
	while (map[i + 1])
	{
		len = ft_strlen(map[i + 1]);
		if (len != ft_strlen(map[i]))
		{
			ft_printf("Error\nMap Must Be Rectangular.\n");
			exit(1);
		}
		i++;
	}
}

/*	Checks that input map has a .ber extension.	*/

void	valid_input(char *str)
{
	int	ext;

	ext = ft_strlen(str) - 4;
	if (ft_strcmp(&str[ext], ".ber"))
	{
		ft_printf("Error\nInvalid Map Extension.\n");
		exit(1);
	}
}
