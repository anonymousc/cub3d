#include <stdlib.h>
#include <stdio.h>
#include "minilibx-linux/mlx.h"

// w = 119;
// s = 115;
// a = 97;
// d = 100;
#define MAP_X  8
#define MAP_Y 8
#define TILE_SIZE 64

int px = 300;
int py = 300;
int player_size = 10;
int mapS = 64;

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


int clear_window (void *mlx, void *win)
{
    mlx_clear_window(mlx, win);
}

int draw_tile(void *mlx, void *win, int x, int y, int color)
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
            mlx_pixel_put(mlx, win, startX + i, startY + j, color);
            j++;
        }
        i++;
    }
    i = 0;
    while (i < TILE_SIZE)
    {
        mlx_pixel_put(mlx, win , startX + i, startY , 0xD3D3D3);
        mlx_pixel_put(mlx, win , startX + i, startY + TILE_SIZE - 1, 0xD3D3D3);

        mlx_pixel_put(mlx, win, startX, startY + i, 0xD3D3D3);
        mlx_pixel_put(mlx, win, startX + TILE_SIZE - 1, startY + i, 0xD3D3D3);
        i++;
    }
    return 0;
}

int draw_map(void *mlx, void *win, int px, int py)
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

            draw_tile(mlx, win, j, i, color);
            j++;
        }
        i++;
    }
    return 0;
}
int player (void *mlx, void *win, int x , int y, int color)
{
    int i = 0;
    while (i < player_size)
    {
        int j = 0;
        while (j < player_size)
        {
            mlx_pixel_put(mlx, win, x + i , y + j , color);
            j++;
        }
        i++;
    }
}

int move (int keycode, void* param)
{
    void **params = (void **)param;
    void *mlx = params[0];
    void *win = params[1];

    if (keycode != 97 && keycode != 100 && keycode != 119 && keycode != 115 && keycode != 65307)
        return 0;
    else if (keycode == 65307)
    {
        mlx_destroy_window(params[0], params[1]);
        exit (0);
    }
    else if (keycode == 97)
        px -= 5;
    else if (keycode == 100)
        px += 5;
    else if (keycode == 119)
        py -= 5;
    else if (keycode = 115)
        py += 5;

    clear_window(mlx, win);
    draw_map(mlx, win, px, py);
    player(mlx, win, px, py, 0x00FF0000);
    return 0;
}   

int main (int ac, char **av)
{
    void *mlx;
    void *win;
    void *img;

    mlx = mlx_init();

    win = mlx_new_window(mlx, TILE_SIZE * 8, TILE_SIZE * 8, "test");

    void *params[] = {mlx, win};

    draw_map(mlx, win, px, py);

    player(mlx, win, px, py, 0x00FF0000);

    mlx_key_hook(win, move, params);

    mlx_loop(mlx);
}