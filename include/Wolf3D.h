#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../minilibx-linux/mlx.h"

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define MAP_X  10
#define MAP_Y 10
#define TILE_SIZE 64
#define PI 3.141592653589793
#define WINDOW_WIDTH TILE_SIZE * MAP_X
#define WINDOW_HEIGHT TILE_SIZE * MAP_Y
#define FOV  60 * (PI / 180)
#define STRIP_WIDTH 1
#define MINIMAP_SCALE_FACTOR 0.2

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
    bool washitvertical;
    float HorzDistance;
    float VertDistance;
    float WallHitX;
    float WallHitY;
    float distance;
    float WallStripHeight;
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
void hor_ver_distances (t_data *data, int i);
int collision(float x, float y);




//// PARSING /////
typedef struct s_parsing
{
    char **coloring;
    char **direction;
    char **map;
}               t_parsing;

void    file_validation(int arg,char **str);

#endif
