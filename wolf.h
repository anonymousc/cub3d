#ifndef WOLF_H
#define WOLF_H

#include <stdlib.h>
#include <stdio.h>
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdbool.h>
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define MAP_X  10
#define MAP_Y 10
#define TILE_SIZE 64
#define PI 3.141592653589793
#define MAPS 64
#define WINDOW_WIDTH TILE_SIZE * MAP_X
#define WINDOW_HEIGHT TILE_SIZE * MAP_Y
#define FOV  60 * (PI / 180)
#define STRIP_WIDTH 10
#define N_R 64

typedef struct s_player 
{
    float px;
    float py;
    int player_size;
    float pangle;
    float turn_direction;
    float walk_direction;
    float move_speed;
    float rotation_speed;
} t_player;

typedef struct s_rays
{
    float ray_angle;
    bool rayfacingUP;
    bool rayfacingDOWN;
    bool rayfacingRIGHT;
    bool rayfacingLEFT;
    float horwallhitX;
    float horwallhitY;
    float vertwallhitX;
    float vertwallhitY;
    bool foundhorwallhit;
    bool foundvertwallhit;
}t_rays;

typedef struct	s_data 
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    t_player *player;
    t_rays *rays;
}t_data; 


float normalize_angle(float angle);
int horz_interception (t_data *data, int i);
int vert_interception (t_data *data, int i);
int collision(float x, float y);

#endif