#include "Wolf3D.h"


unsigned int get_pixel_color(t_data *data, int x, int y) 
{
    char    *dst;
    unsigned int     color = 0;
    
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

    color = (unsigned int)(*(dst + 2)) << 16 | (unsigned int)(*(dst + 1)) << 8 | (unsigned int)(*(dst));

    return color;
}

int main() 
{
    int c = 0xB5ADAB;
    unsigned int *color_buffer = malloc(sizeof(unsigned int) * 64 * 64);
    int width, height;
    t_data *data = malloc(sizeof(t_data));

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 64, 64, "cat");
    data->img = mlx_xpm_file_to_image(data->mlx, "black_cat1.xpm", &width, &height);
    
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    
    int y = 0;
    while ( y < 64) 
    {
        int x = 0;
        while (x < 64) 
        {
            color_buffer[y * 64 + x] = get_pixel_color(data, x, y);
            x++;
        }
        y++;
    }

    printf("Color at (0, 0): %d\n", (unsigned int)color_buffer[70]);
    y = 0;
    while (y < 64)
    {
        int x = 0;
        while(x < 64)
        {
            mlx_pixel_put(data->mlx, data->win, x , y, (unsigned int)color_buffer[y * 64 + x]);
            x++;
        }
        y++;
    }
    mlx_loop(data->mlx);

    return 0;
}
