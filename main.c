/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:17:40 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 19:09:18 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	cast_all_rays(t_data *data)
{
	double	ray_angle;
	int		i;

	ray_angle = data->player->pangle - ((FOV * (PI / 180)) / 2);
	i = 0;
	init_rays(data, &data->rays[0], ray_angle);
	while (i < NUM_OF_RAYS)
	{
		horz_interception(data, i);
		vert_interception(data, i);
		hor_ver_distances(data, i);
		render3dwalls(data, i);
		i++;
	}
}

void	f(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	fill_bg(data);
	cast_all_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	free_map(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < parsing->map->y_len)
	{
		free(parsing->map->map[i]);
		i++;
	}
	free(parsing->map->map);
	free(parsing->map);
}

void	free_parser(t_parsing *parsing)
{
	free_textures(parsing);
	free_coloring(parsing);
	free_map(parsing);
	free(parsing);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = general_init(ac, av);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	init_textures(data);
	fill_color_buffers(data);
	init_player(data->player, data->parsing->map);
	fill_bg(data);
	cast_all_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 02, (1L << 0), keypress, data);
	mlx_hook(data->win, 03, (1L << 1), keyrelease, data);
	mlx_hook(data->win, 17, 0, c, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}
