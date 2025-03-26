/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:00 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/26 21:23:49 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	ft_init_rays(t_data *data, int i)
{
	data->rays[i].rayfacingDOWN = data->rays[i].ray_angle > 0
		&& data->rays[i].ray_angle < PI;
	data->rays[i].rayfacingUP = !data->rays[i].rayfacingDOWN;
	data->rays[i].rayfacingRIGHT = data->rays[i].ray_angle < (PI / 2)
		|| data->rays[i].ray_angle > (3 * PI / 2);
	data->rays[i].rayfacingLEFT = !data->rays[i].rayfacingRIGHT;
	data->rays[i].horwallhitX = 0;
	data->rays[i].horwallhitY = 0;
	data->rays[i].vertwallhitX = 0;
	data->rays[i].vertwallhitY = 0;
	data->rays[i].WallHitX = 0;
	data->rays[i].WallHitY = 0;
	data->rays[i].foundhorwallhit = false;
	data->rays[i].foundvertwallhit = false;
	data->rays[i].washitvertical = false;
	data->rays[i].HorzDistance = 0;
	data->rays[i].VertDistance = 0;
	data->rays[i].distance = 0;
	data->rays[i].xstep = 0;
	data->rays[i].ystep = 0;
}

void	init_rays_angles(t_data *data, t_rays *first_ray, double ray_angle)
{
	int		i;
	double	angle_increment;

	first_ray->ray_angle = normalize_angle(ray_angle);
	angle_increment = FOV / NUM_OF_RAYS;
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

	init_rays_angles(data, first_ray, ray_angle);
	i = -1;
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
