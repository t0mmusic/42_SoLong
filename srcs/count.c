/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:16:03 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/16 18:33:02 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Sets up the position for where the current number will be printed on the
	screen, and also prints the count in the terminal.	*/

void	count_setup(t_mlx *mlx, t_tile *tile, t_num *num, int key)
{
	num->position = 0;
	print_count(tile->move_count, mlx, tile, num);
	num->position = 0;
	print_movement(key);
}

/*	Imports all number images to be used for the counter.	*/

void	find_num(int count, t_mlx *mlx, t_tile *tile, t_num *num)
{
	if (count == 0)
		image_put(mlx, num->zero, num->position, tile->max->y);
	if (count == 1)
		image_put(mlx, num->one, num->position, tile->max->y);
	if (count == 2)
		image_put(mlx, num->two, num->position, tile->max->y);
	if (count == 3)
		image_put(mlx, num->three, num->position, tile->max->y);
	if (count == 4)
		image_put(mlx, num->four, num->position, tile->max->y);
	if (count == 5)
		image_put(mlx, num->five, num->position, tile->max->y);
	if (count == 6)
		image_put(mlx, num->six, num->position, tile->max->y);
	if (count == 7)
		image_put(mlx, num->seven, num->position, tile->max->y);
	if (count == 8)
		image_put(mlx, num->eight, num->position, tile->max->y);
	if (count == 9)
		image_put(mlx, num->nine, num->position, tile->max->y);
}

/*	Figures out which position the current number will be printed.
	it places the most significant number first, then changes the
	position one tile to the right.	*/

void	print_count(int count, t_mlx *mlx, t_tile *tile, t_num *num)
{
	if (count < 9999)
	{
		if (count > 9)
		{
			print_count(count / 10, mlx, tile, num);
			print_count(count % 10, mlx, tile, num);
		}
		else
		{
			find_num(count, mlx, tile, num);
			num->position += 1;
		}
	}
}
