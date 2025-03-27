/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:00:42 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/27 16:04:33 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

bool	collision(double x, double y, t_map *map)
{
	int	mapx;
	int	mapy;

	mapx = (int)(x / TILE_SIZE);
	mapy = (int)(y / TILE_SIZE);
	if (x < 0 || y < 0 || x >= (map->x_len * TILE_SIZE) || y >= (map->y_len
			* TILE_SIZE))
		return (true);
	if (map->map[mapy])
	{
		return (map->map && map->map[mapy][mapx] == 1);
	}
	return (0);
}

void	process_hor_interception(t_data *data, int i, double nexthortouchx,
		double nexthortouchy)
{
	t_map	*map;

	map = data->parsing->map;
	while (nexthortouchx >= 0 && nexthortouchx <= (map->x_len * TILE_SIZE)
		&& nexthortouchy >= 0 && nexthortouchy <= (map->y_len * TILE_SIZE))
	{
		if (collision(nexthortouchx, (nexthortouchy
					- data->rays[i].rayfacingup), map))
		{
			data->rays[i].foundhorwallhit = true;
			data->rays[i].horwallhitx = nexthortouchx;
			data->rays[i].horwallhity = nexthortouchy;
			break ;
		}
		else
		{
			nexthortouchx += data->rays[i].xstep;
			nexthortouchy += data->rays[i].ystep;
		}
	}
}

void	process_vert_interception(t_data *data, int i, double nextverttouchx,
		double nextverttouchy)
{
	t_map	*map;

	map = data->parsing->map;
	while (nextverttouchx >= 0 && nextverttouchx <= (map->x_len * TILE_SIZE)
		&& nextverttouchy >= 0 && nextverttouchy <= (map->y_len * TILE_SIZE))
	{
		if (collision((nextverttouchx - data->rays[i].rayfacingleft),
				nextverttouchy, map))
		{
			data->rays[i].foundvertwallhit = true;
			data->rays[i].vertwallhitx = nextverttouchx;
			data->rays[i].vertwallhity = nextverttouchy;
			break ;
		}
		else
		{
			nextverttouchx += data->rays[i].xstep;
			nextverttouchy += data->rays[i].ystep;
		}
	}
}
