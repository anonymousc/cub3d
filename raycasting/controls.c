/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:11:20 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/29 03:01:13 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	free_all(t_data *data)
{
	free(data->player);
	free_parser(data->parsing);
	free(data->rays);
	mlx_destroy_image(data->mlx, data->texture->east_img);
	mlx_destroy_image(data->mlx, data->texture->west_img);
	mlx_destroy_image(data->mlx, data->texture->north_img);
	mlx_destroy_image(data->mlx, data->texture->south_img);
	free(data->texture->north_texture);
	free(data->texture->south_texture);
	free(data->texture->east_texture);
	free(data->texture->west_texture);
	free(data->texture);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

int	update(t_data *data)
{
	t_map	*map;

	double (next_px), (next_py);
	int (movestep), (sidestep);
	next_px = data->player->px;
	next_py = data->player->py;
	map = data->parsing->map;
	data->player->pangle += normalize_angle(data->player->turn_direction
			* data->player->rotation_speed);
	movestep = data->player->walk_direction * data->player->move_speed;
	sidestep = data->player->sidewalk * data->player->move_speed;
	next_px += cos(data->player->pangle) * movestep;
	next_py += sin(data->player->pangle) * movestep;
	if (data->player->sidewalk == 1 || data->player->sidewalk == -1)
	{
		next_px -= sin(data->player->pangle) * sidestep;
		next_py += cos(data->player->pangle) * sidestep;
	}
	if (!collision(next_px, data->player->py, map))
		data->player->px = next_px;
	if (!collision(data->player->px, next_py, map))
		data->player->py = next_py;
	f(data);
	return (0);
}

int	keypress(int keycode, void *data)
{
	t_data	*img;

	img = (t_data *)data;
	if (keycode == 65307)
	{
		free_all(img);
		exit(0);
	}
	else if (keycode == RIGHT)
		img->player->sidewalk = 1;
	else if (keycode == LEFT)
		img->player->sidewalk = -1;
	if (keycode == UP)
		img->player->walk_direction = 1;
	else if (keycode == DOWN)
		img->player->walk_direction = -1;
	if (keycode == TURN_RIGHT)
		img->player->turn_direction = 1;
	else if (keycode == TURN_LEFT)
		img->player->turn_direction = -1;
	return (0);
}

int	keyrelease(int keycode, void *data)
{
	t_data	*img;

	img = (t_data *)data;
	if (keycode == RIGHT || keycode == LEFT)
		img->player->sidewalk = 0;
	if (keycode == UP || keycode == DOWN)
		img->player->walk_direction = 0;
	if (keycode == TURN_RIGHT || keycode == TURN_LEFT)
		img->player->turn_direction = 0;
	return (0);
}

int	c(void *data)
{
	t_data	*img;

	img = (t_data *)data;
	free_all(img);
	exit(0);
}
