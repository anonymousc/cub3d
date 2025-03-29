#include "Wolf3D.h"

static void texture_failure(t_data *data, int flag)
{
	if (flag == 2)
	{
		mlx_destroy_image(data->mlx, data->texture->north_img);
	}
	if (flag == 3)
	{
		mlx_destroy_image(data->mlx, data->texture->north_img);
		mlx_destroy_image(data->mlx, data->texture->south_img);
	}
	if (flag == 4)
	{
		mlx_destroy_image(data->mlx, data->texture->north_img);
		mlx_destroy_image(data->mlx, data->texture->south_img);
		mlx_destroy_image(data->mlx, data->texture->east_img);	
	}
	free(data->texture);	
}

void	free_all_V2(t_data *data, int flag)
{
	free(data->player);
	free_parser(data->parsing);
	free(data->rays);
	texture_failure(data, flag);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}
