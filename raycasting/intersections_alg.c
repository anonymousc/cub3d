/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_alg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:04:52 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/27 18:06:17 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	horz_interception(t_data *data, int i)
{
	double (nexthortouchy), (nexthortouchx), (yintercept), (xintercept);
	yintercept = (int)(data->player->py / TILE_SIZE) * TILE_SIZE;
	if (data->rays[i].rayfacingdown)
		yintercept += TILE_SIZE;
	xintercept = data->player->px + ((yintercept - data->player->py)
			/ tan(data->rays[i].ray_angle));
	data->rays[i].ystep = TILE_SIZE;
	if (data->rays[i].rayfacingup)
		data->rays[i].ystep *= -1;
	data->rays[i].xstep = TILE_SIZE / tan(data->rays[i].ray_angle);
	if (data->rays[i].rayfacingleft && data->rays[i].xstep > 0)
		data->rays[i].xstep *= -1;
	if (data->rays[i].rayfacingright && data->rays[i].xstep < 0)
		data->rays[i].xstep *= -1;
	nexthortouchx = xintercept;
	nexthortouchy = yintercept;
	process_hor_interception(data, i, nexthortouchx, nexthortouchy);
	return (0);
}

int	vert_interception(t_data *data, int i)
{
	double (nextverttouchx), (nextverttouchy), (xintercept), (yintercept);
	xintercept = (int)(data->player->px / TILE_SIZE) * TILE_SIZE;
	if (data->rays[i].rayfacingright)
		xintercept += TILE_SIZE;
	yintercept = data->player->py + ((xintercept - data->player->px)
			* tan(data->rays[i].ray_angle));
	data->rays[i].xstep = TILE_SIZE;
	if (data->rays[i].rayfacingleft)
		data->rays[i].xstep *= -1;
	data->rays[i].ystep = TILE_SIZE * tan(data->rays[i].ray_angle);
	if (data->rays[i].rayfacingup && data->rays[i].ystep > 0)
		data->rays[i].ystep *= -1;
	if (data->rays[i].rayfacingdown && data->rays[i].ystep < 0)
		data->rays[i].ystep *= -1;
	nextverttouchx = xintercept;
	nextverttouchy = yintercept;
	process_vert_interception(data, i, nextverttouchx, nextverttouchy);
	return (0);
}

bool	was_hit_vertical(t_data *data, int i)
{
	return (data->rays[i].vertdistance < data->rays[i].horzdistance);
}

void	hor_ver_distances(t_data *data, int i)
{
	if (data->rays[i].foundhorwallhit)
		data->rays[i].horzdistance = distance(data->player->px,
				data->player->py, data->rays[i].horwallhitx,
				data->rays[i].horwallhity);
	else
		data->rays[i].horzdistance = INT_MAX;
	if (data->rays[i].foundvertwallhit)
		data->rays[i].vertdistance = distance(data->player->px,
				data->player->py, data->rays[i].vertwallhitx,
				data->rays[i].vertwallhity);
	else
		data->rays[i].vertdistance = INT_MAX;
	if (data->rays[i].horzdistance < data->rays[i].vertdistance)
	{
		data->rays[i].wallhitx = data->rays[i].horwallhitx;
		data->rays[i].wallhity = data->rays[i].horwallhity;
		data->rays[i].distance = data->rays[i].horzdistance;
	}
	else
	{
		data->rays[i].wallhitx = data->rays[i].vertwallhitx;
		data->rays[i].wallhity = data->rays[i].vertwallhity;
		data->rays[i].distance = data->rays[i].vertdistance;
	}
	data->rays[i].washitvertical = was_hit_vertical(data, i);
}
