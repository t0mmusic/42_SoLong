/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:57:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/22 14:11:04 by jbrown           ###   ########.fr       */
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
	it will add the new enemy to the end of the list.	*/

t_enemy	*add_enemy(t_enemy *list, t_enemy *current)
{
	t_enemy	*head;

	head = list;
	if (list->coor->x == 0)
	{
		head = current;
		free(list->coor);
		free(list);
	}
	else
	{
		while (list->next)
			list = list->next;
		list->next = current;
	}
	return (head);
}

/*	Updates the position of the enemy on the map. The position the enemy was
	previously in becomes a '0', the position it is moving to will be a 'B'. 
	It also updates the screen images, placing a floor tile where the enemy
	was and an enemy tile where the enemy has moved to, with a refreshed floor
	tile underneath it.	*/

void	update_enemy(t_enemy *enemy, char **map, t_mlx *mlx)
{
	map[enemy->coor->y][enemy->coor->x] = '0';
	image_put(mlx, mlx->ground, enemy->coor->x, enemy->coor->y);
	map[enemy->coor->y][enemy->coor->x + enemy->direction] = 'B';
	enemy->coor->x += enemy->direction;
	image_put(mlx, mlx->ground, enemy->coor->x, enemy->coor->y);
	image_put(mlx, mlx->enemy, enemy->coor->x, enemy->coor->y);
}

/*	Movement position is set to either increase or decrease in either the x
	coordinate. If the movement is impossible, it will flip from positive to
	negative or vice versa by multiplying by negative 1. It will move on each
	turn if it can move onto a free space or into the player.	*/

void	enemy_movement(t_enemy *enemy, t_tile *tile, char **map, t_mlx *mlx)
{
	t_enemy	*bad;

	bad = enemy;
	player_collision(bad, tile);
	while (bad)
	{
		if (map[bad->coor->y][bad->coor->x + bad->direction] != '0'
			&& map[bad->coor->y][bad->coor->x + bad->direction] != 'P')
			bad->direction *= -1;
		if (map[bad->coor->y][bad->coor->x + bad->direction] == '0'
			|| map[bad->coor->y][bad->coor->x + bad->direction] == 'P')
			update_enemy(bad, map, mlx);
		bad = bad->next;
	}
	if (!tile->quit)
		player_collision(enemy, tile);
}

/*	Checks to see if the player's position is the same as the enemies. If
	They are, it is game over.	*/

void	player_collision(t_enemy *enemy, t_tile *tile)
{
	t_enemy	*bad;

	bad = enemy;
	while (bad)
	{
		if (tile->player->x == bad->coor->x
			&& tile->player->y == bad->coor->y)
		{
			ft_printf("Game over!");
			tile->quit = 2;
		}
		bad = bad->next;
	}
}
