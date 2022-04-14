/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:57:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/14 16:30:48 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Enemies will be in a linked list, the list will update position starting
	from the first element. A valid movement is when it does not interact
	with a wall or another enemy.	*/

/*	Creates a new enemy element and sets its coordinates	*/

t_enemy	*new_enemy(int x, int y)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(*enemy));
	enemy->coor = malloc(sizeof(int) * 2);
	enemy->coor->x = x;
	enemy->coor->y = y;
	enemy->direction = 1;
	enemy->next = NULL;
	return (enemy);
}

/*	If the coordinates are set to 0,0, it will remove the first element
	of the list and replace it with the updated coordinates. Otherwise
	it will add the new enemy to the next element of the list.	*/

t_enemy	*add_enemy(t_enemy *list, t_enemy *current)
{
	t_enemy	*tmp;

	if (list->coor->x == 0)
	{
		tmp = list;
		list = current;
		free(tmp);
	}
	else
	{
		while (list->next)
			list = list->next;
		list->next = current;
	}
	return (list);
}

/*	Updates the position of the enemy on the map. The position the enemy was
	previously in becomes a '0', the position it is moving to will be a 'B'.
	Needs to be updated so that enemy movement goes before player movement
	to prevent player image from being overridden.	*/

void	update_enemy(t_enemy *enemy, char **map, t_mlx *mlx)
{
	map[enemy->coor->y][enemy->coor->x] = '0';
	mlx_put_image_to_window(mlx, mlx->win, mlx->ground,
		enemy->coor->x * mlx->dim->x, enemy->coor->y * mlx->dim->y);
	map[enemy->coor->y][enemy->coor->x + enemy->direction] = 'B';
	enemy->coor->x += enemy->direction;
	mlx_put_image_to_window(mlx, mlx->win, mlx->enemy,
		enemy->coor->x * mlx->dim->x, enemy->coor->y * mlx->dim->y);
}

/*	Movement position is set to either increase or decrease in either the x
	coordinate. If the movement is impossible, it will flip from positive to
	negative or vice versa by multiplying by negative 1. It will not move
	on the turn that it has collided, and will not move at all if it is stuck.
	Need to be updated to stop enemy from moving through wall if it cannot
	move in either direction.	*/

void	enemy_movement(t_enemy *enemy, t_tile *tile, char **map, t_mlx *mlx)
{
	t_enemy	*bad;

	bad = enemy;
	while (bad)
	{
		if (map[bad->coor->y][bad->coor->x + bad->direction] != '0')
			bad->direction *= -1;
		update_enemy(bad, map, mlx);
		bad = bad->next;
	}
	player_collision(enemy, tile);
}

/*	Checks to see if the player's position is the same as the enemies. If
	They are, it is game over.	*/

void	player_collision(t_enemy *enemy, t_tile *tile)
{
	if (tile->player->x == enemy->coor->x
		&& tile->player->y == enemy->coor->y)
	{
		ft_printf("Game over!");
		exit (1);
	}
}
