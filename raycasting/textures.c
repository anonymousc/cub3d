/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:29:12 by aait-bou          #+#    #+#             */
/*   Updated: 2025/03/28 22:14:22 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void *my_mlx_xpm_file_to_image(void *mlx_ptr, char *filename ,t_data *data, int flag)
{
	void *img;
	
	int (width), (height);
	img = mlx_xpm_file_to_image(mlx_ptr, filename, &width, &height);
	if (!img)
		return (free_all_V2(data, flag), exit(1),NULL);
	return (img);
}

void	init_textures(t_data *data)
{
	
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->texture->north_img = my_mlx_xpm_file_to_image(data->mlx,
			get_texture(data, "NO"), data , 1);
	data->texture->north_addr = mlx_get_data_addr(data->texture->north_img,
			&data->texture->bits_per_pixel, &data->texture->line_length,
			&data->texture->endian);
	data->texture->south_img = my_mlx_xpm_file_to_image(data->mlx,
			get_texture(data, "SO"), data , 2);
	data->texture->south_addr = mlx_get_data_addr(data->texture->south_img,
			&data->texture->bits_per_pixel, &data->texture->line_length,
			&data->texture->endian);
	data->texture->east_img = my_mlx_xpm_file_to_image(data->mlx, get_texture(data,
				"EA"), data , 3);
	data->texture->east_addr = mlx_get_data_addr(data->texture->east_img,
			&data->texture->bits_per_pixel, &data->texture->line_length,
			&data->texture->endian);
	data->texture->west_img = my_mlx_xpm_file_to_image(data->mlx, get_texture(data,
				"WE"), data , 4);
	data->texture->west_addr = mlx_get_data_addr(data->texture->west_img,
			&data->texture->bits_per_pixel, &data->texture->line_length,
			&data->texture->endian);
}

char	*get_texture(t_data *data, char *direction)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (*(data->parsing->textures[i].direction) == *direction)
			return (data->parsing->textures[i].filename);
		i++;
	}
	return (NULL);
}

void	fill_buffers(t_data *data)
{
	int (y), (x);
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			data->texture->north_texture[y * 64
				+ x] = get_pixel_color(data->texture, data->texture->north_addr,
					x, y);
			data->texture->south_texture[y * 64
				+ x] = get_pixel_color(data->texture, data->texture->south_addr,
					x, y);
			data->texture->east_texture[y * 64
				+ x] = get_pixel_color(data->texture, data->texture->east_addr,
					x, y);
			data->texture->west_texture[y * 64
				+ x] = get_pixel_color(data->texture, data->texture->west_addr,
					x, y);
			x++;
		}
		y++;
	}
}

void	fill_color_buffers(t_data *data)
{
	data->texture->north_texture = malloc(sizeof(unsigned int) * TILE_SIZE
			* TILE_SIZE);
	data->texture->south_texture = malloc(sizeof(unsigned int) * TILE_SIZE
			* TILE_SIZE);
	data->texture->east_texture = malloc(sizeof(unsigned int) * TILE_SIZE
			* TILE_SIZE);
	data->texture->west_texture = malloc(sizeof(unsigned int) * TILE_SIZE
			* TILE_SIZE);
	fill_buffers(data);
}
