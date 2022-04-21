/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:30:00 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/21 10:00:54 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_enemy(t_enemy *enemy)
{
	t_enemy	*current;

	while (enemy->next)
	{
		current = enemy;
		enemy = enemy->next;
		free(current->coor);
		free(current);
	}
	free(enemy->coor);
	free(enemy);
}

void	free_tile(t_tile *tile)
{
	free(tile->max);
	free(tile->player);
	free(tile);
}

void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->dim);
	free(mlx);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	exit_program(t_tile *tile, char **map)
{
	free_tile(tile);
	free_map(map);
	exit(0);
}
