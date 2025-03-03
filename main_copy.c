#include "Wolf3D.h"

// int num_of_rays = WINDOW_WIDTH / STRIP_WIDTH;
// float distProjPlane;

// int map[MAP_X][MAP_Y] = {
//     {1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,1,0,0,1},
//     {1,0,1,1,1,0,0,0,1,1},
//     {1,0,1,0,0,0,0,0,0,1},
//     {1,1,1,0,0,0,0,1,0,1},
//     {1,0,0,0,0,0,0,1,0,1},
//     {1,0,1,1,0,0,0,0,0,1},
//     {1,0,1,0,1,1,1,1,0,1},
//     {1,0,1,1,1,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1}
// };

// void calculateDistance() 
// {
//     distProjPlane = (WINDOW_WIDTH / 2.0f) / tan(FOV / 2.0f);
// }

// void my_mlx_pixel_put(t_data *data, float x, float y, int color)
// {
// 	char *dst;

// 	dst = data->addr + ((int)y * data->line_length + (int)x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }


// void clear_window (t_data *data)
// {
//     mlx_clear_window(data->mlx, data->win);
// }

// int draw_line(t_data *data, t_player *player, int color)
// {
//     int line_length = 60;

//     int i = 0;
//     while (i < line_length )
//     {
//         int current_x = player->px  + (int)(cos(player->pangle) * i);
//         int current_y = player->py  + (int)(sin(player->pangle) * i);
//         my_mlx_pixel_put(data, current_x, current_y, color);
//         i++;
//     }
//     return 0;
// }


// void init_rays (t_data *data, t_rays *first_ray, float ray_angle)
// {
//     first_ray->ray_angle = normalize_angle(ray_angle);
//     float angle_increment = FOV / num_of_rays;
//     int i = 1;
//     while (i < num_of_rays)
//     {
//         data->rays[i].ray_angle = data->rays[i - 1].ray_angle + angle_increment;
//         i++;
//     }
//     i = 0;
//     while (i < num_of_rays)
//     {
//         data->rays[i].rayfacingDOWN = data->rays[i].ray_angle > 0 && data->rays[i].ray_angle < PI;
//         data->rays[i].rayfacingUP = !data->rays[i].rayfacingDOWN;
//         data->rays[i].rayfacingRIGHT = data->rays[i].ray_angle < (PI / 2) || data->rays[i].ray_angle > (3 * PI / 2);
//         data->rays[i].rayfacingLEFT = !data->rays[i].rayfacingRIGHT;
//         data->rays[i].horwallhitX = 0;
//         data->rays[i].horwallhitY = 0;
//         data->rays[i].vertwallhitX = 0;
//         data->rays[i].vertwallhitY = 0;
//         data->rays[i].WallHitX = 0;
//         data->rays[i].WallHitY = 0;
//         data->rays[i].foundhorwallhit = false;
//         data->rays[i].foundvertwallhit = false;
//         data->rays[i].washitvertical = false;
//         data->rays[i].HorzDistance = 0;
//         data->rays[i].VertDistance = 0;
//         data->rays[i].distance = 0;
//         data->rays[i].WallStripHeight = (TILE_SIZE / data->rays[i].distance) * distProjPlane;
//         i++;
//     }
// }

// void cast_ray(t_data *data, int strip_i)
// {
//     float i = 0.0;
//     float ray_x;
//     float ray_y;
//     int color = 0xFF0000;

//     while (i < data->rays[strip_i].distance )
//     {
//         ray_x = (data->player->px + cos(data->rays[strip_i].ray_angle) * i) ;
//         ray_y = (data->player->py + sin(data->rays[strip_i].ray_angle) * i) ;

//         my_mlx_pixel_put(data, ray_x, ray_y, color);

//         i++;
//     }
// }

// void cast_all_rays(t_data *data)
// {
//     float ray_angle = data->player->pangle - (FOV / 2);
//     int i = 0;
//     int column_id = 0;

//     init_rays(data, &data->rays[0], ray_angle);
//     while (i < num_of_rays)
//     {
//         horz_interception(data, i);
//         vert_interception(data, i);
//         hor_ver_distances(data, i);
//         cast_ray(data, i);
//         i++;
//         column_id++;
//     }
// }

// int draw_tile(t_data *data, int x, int y, int color)
// {
//     int i = 0;
//     int j = 0;
//     int startX = x * TILE_SIZE ; 
//     int startY = y * TILE_SIZE ;

//     while (i < TILE_SIZE ) 
//     {
//         j = 0;
//         while (j < TILE_SIZE ) 
//         {
//             my_mlx_pixel_put(data, startX + i, startY + j, color);
//             j++;
//         }
//         i++;
//     }
//     i = 0;
//     while (i < TILE_SIZE )
//     {
//         my_mlx_pixel_put(data, startX + i, startY , 0xFFFFFF);
//         my_mlx_pixel_put(data, startX + i, startY + (TILE_SIZE - 1) , 0xFFFFFF);
//         my_mlx_pixel_put(data, startX, startY + i, 0xFFFFFF);
//         my_mlx_pixel_put(data, startX + (TILE_SIZE - 1) , startY + i, 0xFFFFFF);
//         i++;
//     }
//     return 0;
// }

// int draw_map(t_data *data)
// {
//     int i = 0;
//     int j = 0;
//     int color;

//     while (i < MAP_Y) 
//     {
//         j = 0;
//         while (j < MAP_X) 
//         {
//             if (map[i][j] == 1)
//                 color = 0xFFFFFF;
//             else
//                 color = 0x000000;
//             draw_tile(data, j, i, color);
//             j++;
//         }
//         i++;
//     }
    
//     return 0;
// }

// void draw_player (t_data *data, t_player *player, int color)
// {
//     int i = 0;
//     cast_all_rays(data);
//     while (i < player->player_size )
//     {
//         int j = 0;
//         while (j < player->player_size )
//         {
//             my_mlx_pixel_put(data, ((player->px - player->player_size / 2) + i)  , ((player->py - player->player_size / 2) + j) , color);
//             j++;
//         }
//         i++;
//     }
//     draw_line(data, player, color);
// }

// int collision(float x, float y)
// {
//     int mapx = (int)(x / TILE_SIZE);
//     int mapy = (int)(y / TILE_SIZE);
    
//     if (x < 0 || y < 0 || x >= (MAP_X * TILE_SIZE) || y >= (MAP_Y * TILE_SIZE))
//         return 1;
        
//     return (map[mapy][mapx] == 1);
// }

// int update(t_data *data)
// {
//     float next_px = data->player->px;
//     float next_py = data->player->py;

//     data->player->pangle += data->player->turn_direction * data->player->rotation_speed;

//     int movestep = data->player->walk_direction * data->player->move_speed;
//     next_px += cos(data->player->pangle) * movestep;
//     next_py += sin(data->player->pangle) * movestep;

//     if (!collision(next_px, data->player->py))
//         data->player->px = next_px;
//     if (!collision(data->player->px, next_py))
//         data->player->py = next_py;

//     clear_window(data);
//     draw_map(data);
//     draw_player(data, data->player, 0x0000FF);

//     data->player->walk_direction = 0;
//     data->player->turn_direction = 0;

//     mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

//     return 0;
// }

// int keypress (int keycode, void *data)
// {
//     t_data *img = (t_data *)data; 
    
//     if (keycode != 97 && keycode != 100 && keycode != 119 && keycode != 115 && keycode != 65307)
//         return 0;
//     if (keycode == 65307)
//     {
//         mlx_destroy_window(img->mlx, img->win);
//         exit (0);
//     }
//     else if (keycode == RIGHT)
//         img->player->turn_direction = 1;
//     else if (keycode == LEFT)
//         img->player->turn_direction = -1;
//     else if(keycode == UP)
//         img->player->walk_direction = 1;
//     else if (keycode == DOWN)
//         img->player->walk_direction = -1;

//     update(img);
//     return 0;
// }

// void init_player (t_player *player)
// {
//     player->px = 225;
//     player->py = 225;
//     player->player_size = 11;
//     player->pangle = 3 * PI / 2;
//     player->turn_direction = 0;
//     player->walk_direction = 0;
//     player->move_speed = 4;
//     player->rotation_speed = 4 * (PI / 180);
// }

int main (int ac, char **av)
{
    char *line = map_validation(file_validation(ac , av));
    free(line);
    // t_data *data = malloc(sizeof(t_data));
    // t_player *player = malloc(sizeof (t_player));
    // t_rays *rays = malloc (sizeof(t_rays) * (WINDOW_WIDTH / STRIP_WIDTH));

    // data->mlx = mlx_init();
    // data->win = mlx_new_window(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y, "cube");
    // data->img = mlx_new_image(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y);
	// data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    // // void *params[] = {data->mlx, data->win};
    // init_player (player);
    // data->player = player;
    // data->rays = rays;
    // draw_map(data);
    // draw_player(data, player, 0x0000FF);
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    // mlx_hook(data->win, 02, (1L << 0), keypress, data);
    // mlx_loop(data->mlx);
}
