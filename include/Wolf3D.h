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

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define TURN_RIGHT 65363
#define TURN_LEFT 65361
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define MAP_X  486
#define MAP_Y 486
#define TILE_SIZE 64
#define PI 3.14159265358979323846
#define TILE_SIZE 64
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FOV  60 * (PI / 180)
#define STRIP_WIDTH 1
#define MINIMAP_SCALE 0.25
#define MINIMAP_TILE_SIZE (TILE_SIZE * MINIMAP_SCALE)

typedef struct s_tex
{
    int iteration_level;
    char *direction;
    char *filename;
}           t_tex;

typedef struct s_color
{
    char *surface;
    int  *rgb;
}               t_color;

typedef struct s_map
{
    double x, y, n;
    int x_len;
    int y_len;
    int **map;
}       t_map;

typedef struct s_parsing
{
    t_tex *textures;
    t_color *coloring;
    t_map *map;
}               t_parsing;

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
    double xstep;
    double ystep;
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
    t_parsing *parsing;
}t_data; 


double normalize_angle(double angle);
int horz_interception (t_data *data, int i, t_map *map);
void process_hor_interception (t_data *data, t_map *map, int i, double nexthortouchX, double nexthortouchY);
int vert_interception (t_data *data, int i, t_map *map);
void process_vert_interception (t_data *data, t_map *map, int i, double nextverttouchX, double nextverttouchY);
void hor_ver_distances (t_data *data, int i);
bool collision(double x, double y, t_map *map);
double distance(double x1, double y1, double x2, double y2);




//// PARSING /////
int         file_validation(int arg,char **str);
t_parsing *map_validation(int fd);
char *detailer_color(char *color);

t_parsing   *fill_texture(char **file_content);
int         fill_coloring(char **line, t_parsing *parsing);
void        free_coloring(t_parsing *parsing);
void        free_textures(t_parsing *parsing);
int get_len(char **s);
char *textures(char *line);
/// APIS /////////
int     ft_strncmp(char *s1 ,char *s2, int n);
int     ft_strcmp(char *s1 ,char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin_map(char *result, char *buffer);
char	**ft_split(char *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
void    ft_free(char **line);
int     ft_atoi(char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_substr(char *s, unsigned int start, size_t len);
int is_space(char c);
int	map_parser(char *file, t_parsing *parsing);
/// NEXT_LINE ////
char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*get_new_line(char *s);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s, char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*set_buffer(char *buffer, char *line);
/////////////////

#endif
