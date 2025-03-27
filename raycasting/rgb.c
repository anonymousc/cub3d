/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:20:11 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/27 03:03:05 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

unsigned int	get_pixel_color(t_texture *texture, void *addr, int x, int y)
{
	char			*dst;
	unsigned int	color;

	color = 0;
	x = x % 64;
	dst = addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	color = (unsigned int)(*(dst + 2) & 0xff) << 16 | ((unsigned int)(*(dst
				+ 1) & 0xff)) << 8 | ((unsigned int)(*dst) & 0xff);
	return (color);
}

void	my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + ((int)y * data->line_length + (int)x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	get_argb(char *c, t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (data->parsing->coloring[i].surface[0] == *c)
			return (create_rgb(data->parsing->coloring[i].rgb[0],
					data->parsing->coloring[i].rgb[1],
					data->parsing->coloring[i].rgb[2]));
		i++;
	}
	return (0);
}
