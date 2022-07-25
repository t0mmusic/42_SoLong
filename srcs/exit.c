/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:30:00 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/25 12:54:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Frees the enemy list one element at a time, including the saved coordinates
	of each enemy.	*/

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

/*	frees the coordinates set for the boundaries of the map and the position
	of the player, and then frees the structure.	*/

void	free_tile(t_tile *tile)
{
	free(tile->player);
	free(tile);
}

/*	removes the mlx window safely and frees the structure.	*/

void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->dim);
	free(mlx);
}

/*	Frees each line of the map array from top to bottom, and then
	frees the map itself.	*/

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

/*	Frees the memory for the structures and the map array and then
	exits the program.	*/

void	exit_program(t_tile *tile, char **map, t_enemy *enemy)
{
	free_enemy(enemy);
	free_tile(tile);
	free_map(map);
	exit(0);
}
