/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:00:42 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/26 21:25:44 by aait-bou         ###   ########.fr       */
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

void	process_hor_interception(t_data *data, int i, double nexthortouchX,
		double nexthortouchY)
{
	t_map	*map;

	map = data->parsing->map;
	while (nexthortouchX >= 0 && nexthortouchX <= (map->x_len * TILE_SIZE)
		&& nexthortouchY >= 0 && nexthortouchY <= (map->y_len * TILE_SIZE))
	{
		if (collision(nexthortouchX, (nexthortouchY
					- data->rays[i].rayfacingUP), map))
		{
			data->rays[i].foundhorwallhit = true;
			data->rays[i].horwallhitX = nexthortouchX;
			data->rays[i].horwallhitY = nexthortouchY;
			break ;
		}
		else
		{
			nexthortouchX += data->rays[i].xstep;
			nexthortouchY += data->rays[i].ystep;
		}
	}
}

void	process_vert_interception(t_data *data, int i, double nextverttouchX,
		double nextverttouchY)
{
	t_map	*map;

	map = data->parsing->map;
	while (nextverttouchX >= 0 && nextverttouchX <= (map->x_len * TILE_SIZE)
		&& nextverttouchY >= 0 && nextverttouchY <= (map->y_len * TILE_SIZE))
	{
		if (collision((nextverttouchX - data->rays[i].rayfacingLEFT),
				nextverttouchY, map))
		{
			data->rays[i].foundvertwallhit = true;
			data->rays[i].vertwallhitX = nextverttouchX;
			data->rays[i].vertwallhitY = nextverttouchY;
			break ;
		}
		else
		{
			nextverttouchX += data->rays[i].xstep;
			nextverttouchY += data->rays[i].ystep;
		}
	}
}
