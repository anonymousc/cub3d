#include "Wolf3D.h"

void fill_bg(t_data *data)
{
    int y;
    int x;

    y = 0;
    while (y < WINDOW_HEIGHT / 2)
    {   
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            my_mlx_pixel_put(data, x, y, get_argb("C", data));
            x++;
        }
        y++;
    }
    while (y < WINDOW_HEIGHT)
    {   
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            my_mlx_pixel_put(data, x, y, get_argb("F", data));
            x++;
        }
        y++;
    }
}

void clear_window (t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
}

void cast_all_rays(t_data *data, t_map *map)
{
    double ray_angle = data->player->pangle - (FOV / 2);
    int i = 0;
    init_rays(data, &data->rays[0], ray_angle);
    while (i < NUM_OF_RAYS)
    {
        horz_interception(data, i, map);
        vert_interception(data, i, map);
        hor_ver_distances(data, i);
        render3DWalls(data , i);
        i++;
    }
}

int WallColor (t_data * data, int i, int textureoffsetX, int textureoffsetY)
{
    int color = 0;
    if (!data->rays[i].washitvertical)
    {
        if (data->rays[i].rayfacingUP)
            color =  data->texture->north_texture[(textureoffsetY * TILE_SIZE) + textureoffsetX];
        if (data->rays[i].rayfacingDOWN)
            color =  data->texture->south_texture[(textureoffsetY * TILE_SIZE) + textureoffsetX];
    }
    else
    {
        if (data->rays[i].rayfacingLEFT)
            color = data->texture->east_texture[(textureoffsetY * TILE_SIZE) + textureoffsetX];
        if (data->rays[i].rayfacingRIGHT)
            color = data->texture->west_texture[(textureoffsetY * TILE_SIZE) + textureoffsetX];
    }
    return color;
}

void draw_strip(t_data *data, int i, double starty, double endy, double wallstripheight)
{
    int textureoffsetY;
    int textureoffsetX;
    int color;

    color = 0;
    if (data->rays[i].washitvertical)
        textureoffsetX = (int)data->rays[i].WallHitY % TILE_SIZE;
    else
        textureoffsetX = (int)data->rays[i].WallHitX % TILE_SIZE;
    int y = starty;
    while (y < endy)
    {
        int DdistanceFromTop = y + (wallstripheight / 2) - (WINDOW_HEIGHT / 2);
        textureoffsetY = DdistanceFromTop * ((double)TILE_SIZE / wallstripheight);
        if (textureoffsetY < 0)
            textureoffsetY = 0;
        color = WallColor(data, i, textureoffsetX, textureoffsetY);
        my_mlx_pixel_put(data, i, y, color);
        y++;
    }
}

void render3DWalls(t_data *data, int i)
{
    double render_center;
    double distProjPlane;
    double correctDistance;
    double wallStripHeight;
    double starty;
    double endy;

    render_center = (WINDOW_HEIGHT / 2);
    distProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
    correctDistance = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player->pangle);
    wallStripHeight = (TILE_SIZE / correctDistance) * distProjPlane;
    starty = render_center - (wallStripHeight / 2);
    endy = render_center + (wallStripHeight / 2);
    if (starty < 0) 
        starty = 0;
    if (endy > WINDOW_HEIGHT) 
        endy = WINDOW_HEIGHT;

    draw_strip(data, i, starty, endy, wallStripHeight);
}

void f(t_data *data)
{
    clear_window(data);
    fill_bg(data);
    cast_all_rays(data, data->parsing->map);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
int update(t_data *data)
{
    t_map *map;  
    double next_px;
    double next_py;
    int movestep;
    int sidestep;

    next_px = data->player->px;
    next_py = data->player->py;
    map = data->parsing->map;    
    data->player->pangle += normalize_angle(data->player->turn_direction * data->player->rotation_speed);
    movestep = data->player->walk_direction * data->player->move_speed;
    sidestep = data->player->sidewalk * data->player->move_speed;
    next_px += cos(data->player->pangle) * movestep;
    next_py += sin(data->player->pangle) * movestep;
    if (data->player->sidewalk == 1 || data->player->sidewalk == -1)
    {
        next_px -= sin(data->player->pangle) * sidestep;
        next_py += cos(data->player->pangle) * sidestep;
    }
    if (!collision(next_px, data->player->py, map))
        data->player->px = next_px;
    if (!collision(data->player->px, next_py, map))
        data->player->py = next_py;
    f(data);
    return 0;
}

int keypress (int keycode, void *data)
{
    t_data *img = (t_data *)data; 
    
    if (keycode == 65307)
    {
        free_parser(img->parsing);
        mlx_destroy_display(img->mlx);
        mlx_destroy_window(img->mlx, img->win);
        exit (0);
    }
    else if (keycode == RIGHT)
        img->player->sidewalk = 1;
    else if (keycode == LEFT)
        img->player->sidewalk = -1;
    if(keycode == UP)
        img->player->walk_direction = 1;
    else if (keycode == DOWN)
        img->player->walk_direction = -1;
    if (keycode == TURN_RIGHT) 
        img->player->turn_direction = 1;
    else if (keycode == TURN_LEFT)
        img->player->turn_direction = -1;
    return 0;
}

int keyrelease (int keycode, void *data)
{
    t_data *img = (t_data *)data; 

    if (keycode == RIGHT || keycode == LEFT)
        img->player->sidewalk = 0;
    if (keycode == UP || keycode == DOWN)
        img->player->walk_direction = 0;
    if (keycode == TURN_RIGHT || keycode == TURN_LEFT)
        img->player->turn_direction = 0;
    return 0;
}

int	c(void *data)
{
    t_data *img = (t_data *)data;
    mlx_destroy_display(img->mlx);
    mlx_destroy_window(img->mlx, img->win);
	exit(0);
}

void fill_color_buffers(t_data *data)
{
    data->texture->north_texture = malloc(sizeof(unsigned int) * TILE_SIZE * TILE_SIZE );
    data->texture->south_texture = malloc(sizeof(unsigned int) * TILE_SIZE * TILE_SIZE );
    data->texture->east_texture = malloc(sizeof(unsigned int) * TILE_SIZE * TILE_SIZE );
    data->texture->west_texture = malloc(sizeof(unsigned int) * TILE_SIZE * TILE_SIZE );
    int y = 0;
    while ( y < 64) 
    {
        int x = 0;
        while (x < 64) 
        {
            data->texture->north_texture[y * 64 + x] = get_pixel_color(data->texture,  data->texture->north_addr, x, y);
            data->texture->south_texture[y * 64 + x] = get_pixel_color(data->texture,  data->texture->south_addr, x, y);
            data->texture->east_texture[y * 64 + x] = get_pixel_color(data->texture,  data->texture->east_addr, x, y);
            data->texture->west_texture[y * 64 + x] = get_pixel_color(data->texture,  data->texture->west_addr, x, y);
            x++;
        }
        y++;
    }
}
char *get_texture(t_data *data , char *direction)
{

    int i = 0;
    while (i < 4)
    {
        if(*(data->parsing->textures[i].direction) == *direction)
            return (data->parsing->textures[i].filename);
        i++;
    }
    return (NULL);
}
void free_map(t_parsing *parsing)
{
    int i = 0;
	while (i < parsing->map->y_len)
	{
		free(parsing->map->map[i]);
		i++;
	}
    free(parsing->map->map);
    free(parsing->map);
}
void free_parser(t_parsing *parsing)
{
    free_textures(parsing);
    free_coloring(parsing);
    free_map(parsing);
    free(parsing);
}

int main (int ac, char **av)
{
    int width, height;

    t_data *data = general_init(ac, av);
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    data->texture->north_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "NO"), &width, &height);
    data->texture->north_addr = mlx_get_data_addr(data->texture->north_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->south_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "SO"), &width, &height);
    data->texture->south_addr = mlx_get_data_addr(data->texture->south_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->east_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "EA") ,&width, &height);
    data->texture->east_addr = mlx_get_data_addr(data->texture->east_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->west_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "WE"), &width, &height);
    data->texture->west_addr = mlx_get_data_addr(data->texture->west_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    fill_color_buffers(data);
    init_player (data->player, data->parsing->map);
    fill_bg(data);
    cast_all_rays(data , data->parsing->map);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 02, (1L << 0), keypress, data);
    mlx_hook(data->win, 03, (1L << 1), keyrelease, data);
    mlx_hook(data->win, 17, 0, c, data);
    mlx_loop_hook(data->mlx, update, data);
    mlx_loop(data->mlx);
}
