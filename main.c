#include <stdlib.h>
#include <stdio.h>
#include "minilibx-linux/mlx.h"
#include <math.h>
// w = 119;
// s = 115;
// a = 97;
// d = 100;

typedef struct	s_data 
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#define MAP_X  8
#define MAP_Y 8
#define TILE_SIZE 64
#define PI 3.141592653589793
float px = 300;
float py = 300;
float pangle = 0.0;
float pdx = 0;
float pdy = 0;
int player_size = 10;
int mapS = 64;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


int map[MAP_X][MAP_Y] = {
    {1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
};


int clear_window (t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
}

int draw_tile(t_data *data, int x, int y, int color)
{
    int i = 0;
    int j = 0;
    int startX = x * TILE_SIZE; 
    int startY = y * TILE_SIZE;

    while (i < TILE_SIZE) 
    {
        j = 0;
        while (j < TILE_SIZE) 
        {
            my_mlx_pixel_put(data, startX + i, startY + j, color);
            j++;
        }
        i++;
    }
    i = 0;
    while (i < TILE_SIZE)
    {
        my_mlx_pixel_put(data, startX + i, startY , 0xD3D3D3);
        my_mlx_pixel_put(data, startX + i, startY + TILE_SIZE - 1, 0xD3D3D3);
        my_mlx_pixel_put(data, startX, startY + i, 0xD3D3D3);
        my_mlx_pixel_put(data, startX + TILE_SIZE - 1, startY + i, 0xD3D3D3);
        i++;
    }
    return 0;
}

int draw_map(t_data *data, int px, int py)
{
    int i = 0;
    int j = 0;
    int color;

    while (i < MAP_Y) 
    {
        j = 0;
        while (j < MAP_X) 
        {
            if (map[i][j] == 1)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            draw_tile(data, j, i, color);
            j++;
        }
        i++;
    }
    return 0;
}

int draw_line(t_data *data, int x, int y, float angle, int color)
{
    int line_length = 60;

    int i = 0;
    while (i < line_length)
    {
        int current_x = x + (int)(cos(angle) * i);
        int current_y = y + (int)(sin(angle) * i);
        my_mlx_pixel_put(data, current_x + (player_size / 2), current_y + (player_size / 2), color);
        i++;
    }
    return 0;
}

int player (t_data *data, int x , int y, float pangle, int color)
{
    int i = 0;
    while (i < player_size)
    {
        int j = 0;
        while (j < player_size)
        {
            my_mlx_pixel_put(data, x + i , y + j, color);
            j++;
        }
        i++;
    }
    draw_line(data , x, y , pangle, color);
}

int collision (float x, float y)
{
    int map_x = (int)((x + player_size) / TILE_SIZE);
    int map_y = (int)((y + player_size) / TILE_SIZE);
    if (map_x < 0 || map_y < 0 || map_x >= MAP_X || map_y >= MAP_Y)
        return 1;
    if (map[map_y][map_x] == 1)
        return 1;
    return 0;
}

int move (int keycode, void *data)
{
    t_data *img = (t_data *)data; 
    int next_px = px;
    int next_py = py;

    if (keycode != 97 && keycode != 100 && keycode != 119 && keycode != 115 && keycode != 65307)
        return 0;
    else if (keycode == 65307)
    {
        mlx_destroy_window(img->mlx, img->win);
        exit (0);
    }
    else if (keycode == 97)
    {
        pangle -= 0.1;
        if (pangle < 0)
            pangle += 2 * PI;
        pdx = cos(pangle) * 5;
        pdy = sin(pangle) * 5;
    }
    else if (keycode == 100)
    {
        pangle += 0.1;
        if (pangle > 2 * PI)
            pangle -= 2 * PI;
        pdx = cos(pangle) * 5;
        pdy = sin(pangle) * 5;

    }
    else if (keycode == 119)
    {
        next_px += pdx;
        next_py += pdy;
    }
    else if (keycode = 115)
    {
        next_px -= pdx;
        next_py -= pdy;
    }

    if (!collision(next_px, py))
        px = next_px;
    if (!collision(px, next_py))
        py = next_py;
    clear_window(img);
    mlx_put_image_to_window(img->mlx,img->win, img->img, 0, 0);
    draw_map(img, px, py);
    player(img, px, py, pangle, 0x00FF0000);
    return 0;
}   

int main (int ac, char **av)
{
    t_data *data = malloc(sizeof(t_data));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, TILE_SIZE * 8, TILE_SIZE * 8, "cube");
    data->img = mlx_new_image(data->mlx, TILE_SIZE * 8, TILE_SIZE * 8);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    void *params[] = {data->mlx, data->win};
   
    

    draw_map(data, px, py);
    player(data, px, py, pangle, 0x00FF0000);
    mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
    mlx_hook(data->win, 02, (1L << 0), move, data);
    mlx_loop(data->mlx);
}
