#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"

#define MAP_X  15
#define MAP_Y 15
#define TILE_SIZE 64
#define PI 3.141592653589793

typedef struct s_parsing
{
    char **coloring;
    char **direction;
    char **map;
}               t_parsing;

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

//// PARSING /////

void    file_validation(int arg,char **str);

#endif
