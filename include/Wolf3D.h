#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

#define BUFFER_SIZE 3
#define TEXTURE_SIZE 4
#if TEXTURE_SIZE > 4
#undef TEXTURE_SIZE
#define TEXTURE_SIZE 4
#endif
#define COLOR_SIZE 3
#if COLOR_SIZE > 3
#undef COLOR_SIZE
#define COLOR_SIZE 3
#endif
// #include "../minilibx-linux/mlx.h"

// #define UP 119
// #define DOWN 115
// #define LEFT 97
// #define RIGHT 100
// #define MAP_X  10
// #define MAP_Y 10
// #define TILE_SIZE 64
// #define PI 3.141592653589793
// #define WINDOW_WIDTH TILE_SIZE * MAP_X
// #define WINDOW_HEIGHT TILE_SIZE * MAP_Y
// #define FOV  60 * (PI / 180)
// #define STRIP_WIDTH 1
// #define MINIMAP_SCALE_FACTOR 0.2
// #if NUM_OF_TEXTURES  > 5 || NUM_OF_TEXTURES < 5
//     #undef NUM_OF_TEXTURES 
//     #define NUM_OF_TEXTURES 5
// #endif
// typedef struct s_player 
// {
//     float px;
//     float py;
//     int player_size;
//     float pangle;
//     float turn_direction;
//     float walk_direction;
//     float move_speed;
//     float rotation_speed;
// } t_player;

// typedef struct s_rays
// {
//     float ray_angle;
//     bool rayfacingUP;
//     bool rayfacingDOWN;
//     bool rayfacingRIGHT;
//     bool rayfacingLEFT;
//     float horwallhitX;
//     float horwallhitY;
//     float vertwallhitX;
//     float vertwallhitY;
//     bool foundhorwallhit;
//     bool foundvertwallhit;
//     bool washitvertical;
//     float HorzDistance;
//     float VertDistance;
//     float WallHitX;
//     float WallHitY;
//     float distance;
//     float WallStripHeight;
// }t_rays;

// typedef struct	s_data 
// {
//     void    *mlx;
//     void    *win;
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
//     t_player *player;
//     t_rays *rays;
// }t_data; 


// float normalize_angle(float angle);
// int horz_interception (t_data *data, int i);
// int vert_interception (t_data *data, int i);
// void hor_ver_distances (t_data *data, int i);
// int collision(float x, float y);




//// PARSING /////
int    file_validation(int arg,char **str);
char	*get_next_line(int fd);
int	ft_strcmp(char *s1 ,char *s2);
int	ft_strncmp(char *s1 ,char *s2, int n);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin_map(char *result, char *buffer);
char	**ft_split(char *s, char c);
/// NEXT_LINE ////
size_t	ft_strlen(char *s);
char	*get_new_line(char *s);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s, char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*set_buffer(char *buffer, char *line);
/////////////////
typedef struct s_tex
{
    int iteration_level;
    char *direction;
    char *filename;
}           t_tex;

typedef struct s_color
{
    int iteration_level;
    char *surface;
    int  *rgb;
}               t_color;
typedef struct s_map
{
    double x, y, n;
    char **map;
}       t_map;

typedef struct s_parsing
{
    t_tex *textures;
    t_color *coloring;
    t_map *map;
}               t_parsing;

char *map_validation(int fd);


#endif
