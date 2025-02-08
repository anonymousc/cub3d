#include "Wolf3D.h"

int num_of_rays = WINDOW_WIDTH / STRIP_WIDTH;
double distProjPlane;

void render3DWalls(t_data *data, int i);

int map[MAP_X][MAP_Y] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,0,0,1,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,1,1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};


void my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char *dst;

	dst = data->addr + ((int)y * data->line_length + (int)x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void fill_bg(t_data *data)
{
    int y = 0;
    int x;
    while (y < WINDOW_HEIGHT)
    {   
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            my_mlx_pixel_put(data, x, y, 0x808080);
            x++;
        }
        y++;
    }
}

void clear_window (t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
}

int draw_line(t_data *data, t_player *player, int color)
{
    int line_length = 60 * MINIMAP_SCALE;
    double scaled_x = player->px * MINIMAP_SCALE;
    double scaled_y = player->py * MINIMAP_SCALE;

    int i = 0;
    while (i < line_length)
    {
        int current_x = scaled_x + (cos(player->pangle) * i);
        int current_y = scaled_y + (sin(player->pangle) * i);
        my_mlx_pixel_put(data, current_x, current_y, color);
        i++;
    }
    return 0;
}

void init_rays (t_data *data, t_rays *first_ray, double ray_angle)
{
    first_ray->ray_angle = normalize_angle(ray_angle);
    double angle_increment = FOV / num_of_rays;
    int i = 1;
    while (i < num_of_rays)
    {
        data->rays[i].ray_angle = normalize_angle(data->rays[i - 1].ray_angle + angle_increment);
        i++;
    }
    i = 0;
    while (i < num_of_rays)
    {
        data->rays[i].rayfacingDOWN = data->rays[i].ray_angle > 0 && data->rays[i].ray_angle < PI;
        data->rays[i].rayfacingUP = !data->rays[i].rayfacingDOWN;
        data->rays[i].rayfacingRIGHT = data->rays[i].ray_angle < (PI / 2) || data->rays[i].ray_angle > (3 * PI / 2);
        data->rays[i].rayfacingLEFT = !data->rays[i].rayfacingRIGHT;
        data->rays[i].horwallhitX = 0;
        data->rays[i].horwallhitY = 0;
        data->rays[i].vertwallhitX = 0;
        data->rays[i].vertwallhitY = 0;
        data->rays[i].WallHitX = 0;
        data->rays[i].WallHitY = 0;
        data->rays[i].foundhorwallhit = false;
        data->rays[i].foundvertwallhit = false;
        data->rays[i].washitvertical = false;
        data->rays[i].HorzDistance = 0;
        data->rays[i].VertDistance = 0;
        data->rays[i].distance = 0;
        i++;
    }
}


void cast_ray(t_data *data, int strip_i)
{
    double i = 0.0;
    double ray_x;
    double ray_y;
    int color = 0xFF0000;

    while (i < data->rays[strip_i].distance)
    {
        ray_x = (data->player->px + cos(data->rays[strip_i].ray_angle) * i) * MINIMAP_SCALE;
        ray_y = (data->player->py + sin(data->rays[strip_i].ray_angle) * i) * MINIMAP_SCALE;
        my_mlx_pixel_put(data, ray_x, ray_y, color);
        i++;
    }
}

void *cast_all_rays(void *arg)
{
    t_data *data = (t_data *)arg;
    double ray_angle = data->player->pangle - (FOV / 2);
    int i = 0;
    int column_id = 0;

    init_rays(data, &data->rays[0], ray_angle);
    while (i < num_of_rays)
    {
        horz_interception(data, i);
        vert_interception(data, i);
        hor_ver_distances(data, i);
        render3DWalls(data , i);
        i++;
        column_id++;
    }
    return NULL;
}
int draw_rays(t_data *data)
{
    int i = 0;
    while (i < num_of_rays)
    {
        cast_ray(data, i);
        i++;
    }
}

void draw_rect(t_data *data, double startx, double starty, double endx, double endy)
{
    double x = startx;
    while (x < endx)
    {
        double y = starty;
        while (y < endy)
        {
            my_mlx_pixel_put(data, x, y, 0xFFFFFF);
            y++;
        }
        x++;
    }
}

void render3DWalls(t_data *data, int i)
{
    double distProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
    double wallStripHeight = (TILE_SIZE / data->rays[i].distance) * distProjPlane;

    double starty = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
    double endy = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);

    if (starty < 0) 
        starty = 0;
    if (endy > WINDOW_HEIGHT) 
        endy = WINDOW_HEIGHT;

    draw_rect(data, i * STRIP_WIDTH, starty, (i + 1) * STRIP_WIDTH, endy);

}

int draw_tile(t_data *data, int x, int y, int color)
{
    int i = 0;
    int j = 0;
    int startX = x * MINIMAP_TILE_SIZE;
    int startY = y * MINIMAP_TILE_SIZE;

    while (i < MINIMAP_TILE_SIZE)
    {
        j = 0;
        while (j < MINIMAP_TILE_SIZE)
        {
            my_mlx_pixel_put(data, startX + i, startY + j, color);
            j++;
        }
        i++;
    }
    return 0;
}

int draw_map(t_data *data)
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
            draw_tile(data, j, i, color);
            j++;
        }
        i++;
    }
    
    return 0;
}

void draw_player(t_data *data, t_player *player, int color)
{
    double scaled_size = player->player_size * MINIMAP_SCALE;
    double scaled_x = player->px * MINIMAP_SCALE;
    double scaled_y = player->py * MINIMAP_SCALE;
    
    int i = 0;
    while (i < scaled_size)
    {
        int j = 0;
        while (j < scaled_size)
        {
            my_mlx_pixel_put(data, 
                ((scaled_x - scaled_size / 2) + i),
                ((scaled_y - scaled_size / 2) + j),
                color);
            j++;
        }
        i++;
    }
    draw_line(data, player, color);
}

bool collision(double x, double y)
{
    int mapx = (int)(x / TILE_SIZE);
    int mapy = (int)(y / TILE_SIZE);
    
    if (x < 0 || y < 0 || x >= (MAP_X * TILE_SIZE) || y >= (MAP_Y * TILE_SIZE))
        return true;
        
    return (map[mapy][mapx] == 1);
}

int update(t_data *data)
{
    double next_px = data->player->px;
    double next_py = data->player->py;

    data->player->pangle += data->player->turn_direction * data->player->rotation_speed;

    int movestep = data->player->walk_direction * data->player->move_speed;
    next_px += cos(data->player->pangle) * movestep;
    next_py += sin(data->player->pangle) * movestep;

    if (!collision(next_px, data->player->py))
        data->player->px = next_px;
    if (!collision(data->player->px, next_py))
        data->player->py = next_py;

    clear_window(data);
    fill_bg(data);
    cast_all_rays(data);
    draw_map(data);
    draw_player(data, data->player, 0x0000FF);
    draw_rays(data);

    data->player->walk_direction = 0;
    data->player->turn_direction = 0;

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

    return 0;
}

int keypress (int keycode, void *data)
{
    t_data *img = (t_data *)data; 

    
    if (keycode == 65307)
    {
        mlx_destroy_window(img->mlx, img->win);
        free(img->player);
        free(img->rays);
        free(img);
        exit (0);
    }
    else if(keycode == UP)
        img->player->walk_direction = 1;
    else if (keycode == DOWN)
        img->player->walk_direction = -1;
    else if (keycode == TURN_RIGHT || keycode == RIGHT) 
        img->player->turn_direction = 1;
    else if (keycode == TURN_LEFT || keycode == LEFT)
        img->player->turn_direction = -1;

    update(img);
    return 0;
}

void init_player (t_player *player)
{
    player->px = 225;
    player->py = 225;
    player->player_size = 11;
    player->pangle = 3 * PI / 2;
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->move_speed = 4;
    player->rotation_speed = 4 * (PI / 180);
}

int	c(void)
{
	exit(0);
}

void init_threads(t_data *data)
{
    int i = 0;
    while (i < num_of_rays)
    {
        data->threads[i].id = i;
        data->threads[i].ray_id = i;
        pthread_create(&data->threads[i].id, NULL, cast_all_rays, data);
        i++;
    }
    i = 0;
    while (i < num_of_rays)
    {
        pthread_join(data->threads[i].id, NULL);
        i++;
    }

}

int main (int ac, char **av)
{
    (void)ac , (void)av;
    t_data *data = malloc(sizeof(t_data));
    t_player *player = malloc(sizeof (t_player));
    t_rays *rays = malloc (sizeof(t_rays) * (WINDOW_WIDTH / STRIP_WIDTH));

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y, "cube");
    data->img = mlx_new_image(data->mlx, TILE_SIZE * MAP_X, TILE_SIZE * MAP_Y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    init_player (player);
    init_threads(data);
    data->player = player;
    data->rays = rays;
    fill_bg(data);
    cast_all_rays(data);
    draw_map(data);
    draw_player(data, player, 0x0000FF);
    draw_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 02, (1L << 0), keypress, data);
    mlx_hook(data->win, 17, 0, c, data);
    mlx_loop(data->mlx);
}
