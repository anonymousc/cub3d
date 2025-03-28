/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:11:26 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/27 19:11:27 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	fill_bg(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, get_argb("C", data));
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, get_argb("F", data));
			x++;
		}
		y++;
	}
}

int	wallcolor(t_data *data, int i, int textureoffsetx, int textureoffsety)
{
	int	color;

	color = 0;
	if (!data->rays[i].washitvertical)
	{
		if (data->rays[i].rayfacingup)
			color = data->texture->north_texture[(textureoffsety * TILE_SIZE)
				+ textureoffsetx];
		if (data->rays[i].rayfacingdown)
			color = data->texture->south_texture[(textureoffsety * TILE_SIZE)
				+ textureoffsetx];
	}
	else
	{
		if (data->rays[i].rayfacingleft)
			color = data->texture->east_texture[(textureoffsety * TILE_SIZE)
				+ textureoffsetx];
		if (data->rays[i].rayfacingright)
			color = data->texture->west_texture[(textureoffsety * TILE_SIZE)
				+ textureoffsetx];
	}
	return (color);
}

void	draw_strip(t_data *data, int i, double starty, double endy)
{
	int	textureoffsety;
	int	textureoffsetx;
	int	color;
	int	y;
	int	ddistancefromtop;

	color = 0;
	if (data->rays[i].washitvertical)
		textureoffsetx = (int)data->rays[i].wallhity % TILE_SIZE;
	else
		textureoffsetx = (int)data->rays[i].wallhitx % TILE_SIZE;
	y = starty;
	while (y < endy)
	{
		ddistancefromtop = y + (data->rays[i].wallstripheight / 2)
			- (WINDOW_HEIGHT / 2);
		textureoffsety = ddistancefromtop * ((double)TILE_SIZE
				/ data->rays[i].wallstripheight);
		if (textureoffsety < 0)
			textureoffsety = 0;
		color = wallcolor(data, i, textureoffsetx, textureoffsety);
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}
}

void	render3dwalls(t_data *data, int i)
{
	double	render_center;
	double	distprojplane;
	double	correctdistance;
	double	starty;
	double	endy;

	render_center = (WINDOW_HEIGHT / 2);
	distprojplane = (WINDOW_WIDTH / 2) / tan((FOV * (PI / 180)) / 2);
	correctdistance = data->rays[i].distance * cos(data->rays[i].ray_angle
			- data->player->pangle);
	data->rays[i].wallstripheight = (TILE_SIZE / correctdistance)
		* distprojplane;
	starty = render_center - (data->rays[i].wallstripheight / 2);
	endy = render_center + (data->rays[i].wallstripheight / 2);
	if (starty < 0)
		starty = 0;
	if (endy > WINDOW_HEIGHT)
		endy = WINDOW_HEIGHT;
	draw_strip(data, i, starty, endy);
}
