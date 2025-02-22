#ifndef Wolf3D_H
#define Wolf3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <stdatomic.h>
#include "../minilibx-linux/mlx.h"

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define TURN_RIGHT 65363
#define TURN_LEFT 65361
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define MAP_X  15
#define MAP_Y 15
#define TILE_SIZE 64
#define PI 3.141592653589793
#define WINDOW_WIDTH TILE_SIZE * MAP_X
#define WINDOW_HEIGHT TILE_SIZE * MAP_Y
#define FOV  60 * (PI / 180)
#define STRIP_WIDTH 1
#define MINIMAP_SCALE 0.25
#define MINIMAP_TILE_SIZE (TILE_SIZE * MINIMAP_SCALE)

typedef struct s_texture
{
    unsigned int *north_texture;
    unsigned int *south_texture;
    unsigned int *east_texture;
    unsigned int *west_texture;
    void    *north_img;
    void    *south_img;
    void    *east_img;
    void    *west_img;
    void    *north_addr;
    void    *south_addr;
    void    *east_addr;
    void    *west_addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_texture;

typedef struct s_player 
{
    double px;
    double py;
    int player_size;
    double pangle;
    double turn_direction;
    double walk_direction;
    double sidewalk;
    double move_speed;
    double rotation_speed;
} t_player;

typedef struct s_rays
{
    double ray_angle;
    bool rayfacingUP;
    bool rayfacingDOWN;
    bool rayfacingRIGHT;
    bool rayfacingLEFT;
    double horwallhitX;
    double horwallhitY;
    double vertwallhitX;
    double vertwallhitY;
    bool foundhorwallhit;
    bool foundvertwallhit;
    bool washitvertical;
    double HorzDistance;
    double VertDistance;
    double WallHitX;
    double WallHitY;
    double distance;
    double WallStripHeight;
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
    t_texture *texture;
}t_data; 


double normalize_angle(double angle);
int horz_interception (t_data *data, int i);
int vert_interception (t_data *data, int i);
void hor_ver_distances (t_data *data, int i);
bool collision(double x, double y);
void calculateDistance();




//// PARSING /////
typedef struct s_parsing
{
    char **coloring;
    char **direction;
    char **map;
}               t_parsing;

void    file_validation(int arg,char **str);

#endif
