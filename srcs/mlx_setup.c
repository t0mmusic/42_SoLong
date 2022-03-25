#include "solong.h"

/*	Checks map to see what has changed and updates the images accordingly 
	Doing this every time would be slow as only some tiles will need
	to be updated. Consider making this an initilisation. */

void	update_map(t_coor *pixel, char **map, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x <= pixel->x_max)
	{
		y = 0;
		while (y <= pixel->y_max)
		{
			if (map[x][y] == 'P')
				mlx_put_image_to_window(mlx, mlx->win, mlx->player, y * 50, x * 50);
			if (map[x][y] == '0')
				mlx_put_image_to_window(mlx, mlx->win, mlx->ground, y * 50, x * 50);
			if (map[x][y] == '1')
				mlx_put_image_to_window(mlx, mlx->win, mlx->wall, y * 50, x * 50);
			if (map[x][y] == 'E')
				mlx_put_image_to_window(mlx, mlx->win, mlx->exit, y * 50, x * 50);
			if (map[x][y] == 'C')
				mlx_put_image_to_window(mlx, mlx->win, mlx->item, y * 50, x * 50);
			y++;
		}
		x++;
	}
}

/*	Creates an mlx instance and a graphical window, then assigns all of the images
	into pointers. */

t_mlx	*init_mlx(t_coor *tile)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = malloc(sizeof(*mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, (tile->y_max + 1) * 50, (tile->x_max + 1) * 50, "Hello world!");//tile->x_max * 50, tile->y_max * 50
	mlx->player = mlx_xpm_file_to_image(mlx->mlx, "game_images/player.xpm", &x, &y);
	mlx->ground = mlx_xpm_file_to_image(mlx->mlx, "game_images/floor.xpm", &x, &y);
	mlx->wall = mlx_xpm_file_to_image(mlx->mlx, "game_images/wall.xpm", &x, &y);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "game_images/exit.xpm", &x, &y);
	mlx->item = mlx_xpm_file_to_image(mlx->mlx, "game_images/item.xpm", &x, &y);
	return (mlx);
}

/*	Loops until exit is found or exit is forced. Player commands are
	currently entered using scanf. 

void	loop_function(char **map, t_coor *location)
{
	char	*input;
	t_mlx	*mlx;

	mlx = init_mlx();
	ft_printf("HELLO\n");
	find_pieces(map, location);
	//update_map(location, map, mlx);
	location->exit = 1;
	location->collect = 0;
	location->exit_swap = 0;
	while (location->exit)
	{
		input = malloc(10);
		scanf("%s", input);
		ft_printf("input: %s\n", input);
		if (!ft_strcmp(input, "w") || !ft_strcmp(input, "a")
			|| !ft_strcmp(input, "s") || !ft_strcmp(input, "d"))
			move_check(1, map, location, mlx);
		if (!ft_strcmp(input, "exit"))
			location->exit = 0;
		free(input);
		input = NULL;
	}
	mlx_loop(mlx->mlx);
}*/

int	key_press(int key, t_data *data)
{
	t_mlx	*mlx;
	t_coor	*tile;
	char	**map;

	map = data->map;
	tile = data->tile;
	mlx = data->mlx;
	tile->exit = 1;
	if (key == 13 || key == 0 || key == 1 || key == 2)
		move_check(key, map, tile, mlx);
	if (!(tile->exit) || key == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	ft_printf("%i\n", key);//change to print movement direction
	return (0);
}

void	user_input(char **map, t_coor *tile)
{
	int		key;
	t_mlx	*mlx;
	t_data	*data;

	tile->collect = 0;
	data = malloc(sizeof(*data));
	find_pieces(map, tile);
	mlx = init_mlx(tile);
	data->map = map;
	data->mlx = mlx;
	data->tile = tile;
	update_map(tile, map, mlx);
	key = mlx_key_hook(mlx->win, key_press, data);
	mlx_loop(mlx->mlx);
}