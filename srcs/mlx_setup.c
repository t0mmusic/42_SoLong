/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:20:46 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/21 16:37:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Prints the images. This function is used to reduce the number of lines used
	by other functions.	*/

void	image_put(t_mlx *mlx, void *img, int x, int y)
{
	mlx_put_image_to_window(mlx, mlx->win,
		img, x * mlx->dim->x, y * mlx->dim->y);
}

/*	Checks to see if the key that was pressed by the user
	was valid for movement or to exit the program. If it was
	for movement, it will use move_check to see if the movement
	is possible, then it will print the direction of movement. 
	It then move each enemy in the enemy list and checks to see if
	the player was on the same tile as the enemy both before and
	after it moved.	If the user pressed 'Esc', it will free all
	allocated memory and exit the program.	*/

int	key_press(int key, t_data *data)
{
	t_mlx	*mlx;
	t_tile	*tile;
	char	**map;

	map = data->map;
	tile = data->tile;
	mlx = data->mlx;
	tile->quit = 1;
	if (key == 13 || key == 0 || key == 1 || key == 2)
		move_check(key, map, tile, mlx);
	if (data->enemy->coor->x != 0)
		enemy_movement(data->enemy, tile, map, mlx);
	if (!(tile->quit) || key == 53)
	{
		free_mlx(mlx);
		free_enemy(data->enemy);
		free(data->num);
		free(data);
		exit_program(tile, map);
	}
	data->num->position = 0;
	print_count(tile->move_count, mlx, tile, data->num);
	data->num->position = 0;
	print_movement(key);
	return (0);
}

/*	Compiles all of the structures used by the key hook into one
	larger structure so that all of the data can be used in later
	functions. I really wish I could use global variables.	*/

void	collect_data(t_list *map_list, t_tile *tile)
{
	t_mlx	*mlx;
	t_data	*data;
	t_enemy	*enemy;
	t_num	*num;
	char	**map;

	num = NULL;
	enemy = new_enemy(0, 0);
	map = map_init(map_list);
	rectangle_check(map, tile);
	enemy = find_pieces(map, tile, enemy);
	error_check(map, tile);
	data = malloc(sizeof(*data));
	mlx = init_mlx(tile);
	num = get_numbers(mlx, num);
	image_put(mlx, num->zero, 0, tile->max->y + 2);
	data->num = num;
	data->map = map;
	data->mlx = mlx;
	data->tile = tile;
	data->enemy = enemy;
	initialise_map(tile, map, mlx);
	user_input(data);
}

/*	Sets up the mlx loop so that the program stays open to
	recieve user inputs.	*/

void	user_input(t_data *data)
{
	int		key;

	key = mlx_key_hook(data->mlx->win, key_press, data);
	mlx_loop(data->mlx->mlx);
}
