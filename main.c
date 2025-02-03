#include "Cub3D.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
char	*ft_strncmp(char *dest, char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest && src && dest[i] && src[i] && dest[i] == src )
	{
		/* code */
	}
	
	return (NULL);
}
void extension_validation(char *str)
{
	if(ft_strlen(ft_strchr(str , '.')) != 4 && !ft_strncmp(ft_strchr(str , '.') , ".cub", 4))
	{
		printf("data == %s || %s\n", str ,ft_strchr(str , '.'));
		return (printf("Invalid map extension\n") ,exit(1), (void)0);
	}
}

void file_validation(int arg,char **str)
{
	if(arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit (1);
	}
	extension_validation(str[1]);
	int fd = open(str[1] , O_RDWR);
	if(fd == -1)
		return (close(fd) ,printf("Invalid file\n") ,exit(1), (void)0);
	close(fd);
}

int main(int ac , char **av)
{
	file_validation(ac, av);
// w = 119;
// s = 115;
// a = 97;
// d = 100;

float px = 250;
float py = 250;
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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
    {1,0,1,1,0,1,0,1,1,1,0,1,0,1,1},
    {1,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,0,1,1,1,1,1,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,0,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void clear_window (t_data *data)
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
	(void)px;
	(void)py;
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

void player (t_data *data, int x , int y, float pangle, int color)
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

int collision(float x, float y)
{
    int top_left_x = (int)(x / TILE_SIZE);
    int top_left_y = (int)(y / TILE_SIZE);
    
    int top_right_x = (int)((x + player_size) / TILE_SIZE);
    int top_right_y = (int)(y / TILE_SIZE);
    
    int bottom_left_x = (int)(x / TILE_SIZE);
    int bottom_left_y = (int)((y + player_size) / TILE_SIZE);
    
    int bottom_right_x = (int)((x + player_size) / TILE_SIZE);
    int bottom_right_y = (int)((y + player_size) / TILE_SIZE);
    
    if (top_left_x < 0 || top_left_y < 0 || bottom_right_x >= MAP_X || bottom_right_y >= MAP_Y)
        return 1;
        
    if (map[top_left_y][top_left_x] == 1 ||
        map[top_right_y][top_right_x] == 1 ||
        map[bottom_left_y][bottom_left_x] == 1 ||
        map[bottom_right_y][bottom_right_x] == 1)
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
    else if (keycode == 115)
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
	(void)ac;
	(void)av;
	file_validation(ac, av);
    t_data *data = malloc(sizeof(t_data));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y, "cube");
    data->img = mlx_new_image(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    draw_map(data, px, py);
    player(data, px, py, pangle, 0x00FF0000);
    mlx_put_image_to_window(data->mlx,data->win, data->img, 0, 0);
    mlx_hook(data->win, 02, (1L << 0), move, data);
    mlx_loop(data->mlx);
	return 0;
}
