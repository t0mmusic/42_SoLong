/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/14 13:48:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Checks that map is rectangular. */

void	rectangle_check(char **map, t_tile *tile)
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
			exit_program(tile, map);
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
