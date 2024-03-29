/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:01:59 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/25 13:37:06 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	When the user hits the esc key, this function will exit the program.	*/

int	pause_game(int key, t_data *data)
{
	t_tile	*tile;
	t_enemy	*enemy;
	char	**map;

	map = data->map;
	tile = data->tile;
	enemy = data->enemy;
	if (key == EXIT)
	{
		free_mlx(data->mlx);
		free(data->num);
		free(data);
		exit_program(tile, map, enemy);
	}
	return (0);
}

/*	This function will keep the program paused until the user hits the 
	esc key.	*/

void	game_over(t_data *data)
{
	int	key;

	if (data->tile->quit == 1)
		image_put(data->mlx, data->mlx->success, 9, data->tile->max_y);
	if (data->tile->quit == 2)
		image_put(data->mlx, data->mlx->gameover, 9, data->tile->max_y);
	key = mlx_key_hook(data->mlx->win, pause_game, data);
	(void)key;
	mlx_loop(data->mlx->mlx);
}

/*	Checks to see if the key that was pressed by the user
	was valid for movement or to exit the program. If it was
	for movement, it will use move_check to see if the movement
	is possible, then it will print the direction of movement. 
	It then move each enemy in the enemy list and checks to see if
	the player was on the same tile as the enemy both before and
	after it moved.	If the user pressed 'Esc', it will go to the pause
	function above, where it will exit the program.	*/

int	key_press(int key, t_data *data)
{
	t_mlx	*mlx;
	t_tile	*tile;
	char	**map;

	map = data->map;
	tile = data->tile;
	mlx = data->mlx;
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		move_check(key, map, tile, mlx);
		if (data->enemy->coor->x != 0)
			enemy_movement(data->enemy, tile, map, mlx);
	}
	count_setup(mlx, tile, data->num, key);
	if (key == EXIT)
	{
		pause_game(key, data);
	}
	if (tile->quit)
		game_over(data);
	return (0);
}

/*	Sets up the mlx loop so that the program stays open to
	recieve user inputs. This function links to the function that handles
	player movement.	*/

void	user_input(t_data *data)
{
	int		key;

	key = mlx_key_hook(data->mlx->win, key_press, data);
	(void)key;
	mlx_loop(data->mlx->mlx);
}
