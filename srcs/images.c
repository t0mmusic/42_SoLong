/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:13:04 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/22 14:23:55 by jbrown           ###   ########.fr       */
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

/*	Creates an mlx instance and a graphical window, then assigns 
	all of the images into pointers. The tile size is determined
	by the dimensions of the floor tiles, so that image is initialised
	first. The window size is the maximum x and y coordiates multiplied
	by the floor tile size.	The x and y coordinates of the other images
	doesn't get used anywhere, so they are just stored in integers for
	the duration of this function.	*/

t_mlx	*init_mlx(t_tile *tile)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = malloc(sizeof(*mlx));
	mlx->dim = malloc(sizeof(int) * 2);
	mlx->mlx = mlx_init();
	mlx->ground = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/floor.xpm", &mlx->dim->x, &mlx->dim->y);
	mlx->win = mlx_new_window(mlx->mlx, tile->max->x * mlx->dim->x,
			(tile->max->y * mlx->dim->y) + mlx->dim->y, "So Long!");
	mlx->player = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/player.xpm", &x, &y);
	mlx->wall = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/wall.xpm", &x, &y);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/exit.xpm", &x, &y);
	mlx->item = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/item.xpm", &x, &y);
	mlx->enemy = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/enemy.xpm", &x, &y);
	image_extras(mlx);
	return (mlx);
}

/*	Adds the number images into the num structure.	*/

t_num	*get_numbers(t_mlx *mlx, t_num *num)
{
	int		x;
	int		y;

	num = malloc(sizeof(*num));
	num->zero = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/zero.xpm", &x, &y);
	num->one = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/one.xpm", &x, &y);
	num->two = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/two.xpm", &x, &y);
	num->three = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/three.xpm", &x, &y);
	num->four = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/four.xpm", &x, &y);
	num->five = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/five.xpm", &x, &y);
	num->six = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/six.xpm", &x, &y);
	num->seven = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/seven.xpm", &x, &y);
	num->eight = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/eight.xpm", &x, &y);
	num->nine = mlx_xpm_file_to_image(mlx->mlx,
			"numbers/nine.xpm", &x, &y);
	return (num);
}

/*	Imports the images that are just used to convey
	information; the instructions and the end messages.	*/

void	image_extras(t_mlx *mlx)
{
	int	x;
	int	y;

	mlx->ins = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/instructions.xpm", &x, &y);
	mlx->gameover = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/gameover.xpm", &x, &y);
	mlx->success = mlx_xpm_file_to_image(mlx->mlx,
			"tiles/success.xpm", &x, &y);
}
