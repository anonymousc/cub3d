/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:00 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/27 17:53:06 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	ft_init_rays(t_data *data, int i)
{
	data->rays[i].rayfacingdown = data->rays[i].ray_angle > 0
		&& data->rays[i].ray_angle < PI;
	data->rays[i].rayfacingup = !data->rays[i].rayfacingdown;
	data->rays[i].rayfacingright = data->rays[i].ray_angle < (PI / 2)
		|| data->rays[i].ray_angle > (3 * PI / 2);
	data->rays[i].rayfacingleft = !data->rays[i].rayfacingright;
	data->rays[i].horwallhitx = 0;
	data->rays[i].horwallhity = 0;
	data->rays[i].vertwallhitx = 0;
	data->rays[i].vertwallhity = 0;
	data->rays[i].wallhitx = 0;
	data->rays[i].wallhity = 0;
	data->rays[i].foundhorwallhit = false;
	data->rays[i].foundvertwallhit = false;
	data->rays[i].washitvertical = false;
	data->rays[i].horzdistance = 0;
	data->rays[i].vertdistance = 0;
	data->rays[i].distance = 0;
	data->rays[i].xstep = 0;
	data->rays[i].ystep = 0;
	data->rays[i].wallstripheight = 0;
}

void	init_rays_angles(t_data *data, t_rays *first_ray, double ray_angle)
{
	int		i;
	double	angle_increment;

	first_ray->ray_angle = normalize_angle(ray_angle);
	angle_increment = (FOV * (PI / 180)) / NUM_OF_RAYS;
	i = 1;
	while (i < NUM_OF_RAYS)
	{
		data->rays[i].ray_angle = normalize_angle(data->rays[i - 1].ray_angle
				+ angle_increment);
		i++;
	}
}

void	init_rays(t_data *data, t_rays *first_ray, double ray_angle)
{
	int	i;

	i = -1;
	init_rays_angles(data, first_ray, ray_angle);
	while (++i < NUM_OF_RAYS)
	{
		ft_init_rays(data, i);
	}
}

void	init_player(t_player *player, t_map *map)
{
	player->px = map->x;
	player->py = map->y;
	player->player_size = 1;
	player->pangle = map->n;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->sidewalk = 0;
	player->move_speed = 2;
	player->rotation_speed = 0.5 * (PI / 180);
}

t_data	*general_init(int ac, char **av)
{
	t_parsing	*parser;
	t_data		*data;
	t_player	*player;
	t_rays		*rays;
	t_texture	*textures;

	(void)ac, (void)av;
	parser = map_validation(file_validation(ac, av));
	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	rays = malloc(sizeof(t_rays) * (WINDOW_WIDTH / STRIP_WIDTH));
	textures = malloc(sizeof(t_texture));
	data->parsing = parser;
	data->player = player;
	data->rays = rays;
	data->texture = textures;
	return (data);
}
