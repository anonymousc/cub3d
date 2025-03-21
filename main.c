#include "Wolf3D.h"

int num_of_rays = WINDOW_WIDTH;
double distProjPlane;
double render_center = (WINDOW_HEIGHT / 2);
void render3DWalls(t_data *data, int i);


unsigned int get_pixel_color(t_texture *texture, void *addr, int x, int y) 
{
    char    *dst;
    unsigned int     color = 0;

    x = x % 64;
    dst = addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));

    color = (unsigned int)(*(dst + 2) & 0xff) << 16 | (unsigned int)(*(dst + 1) & 0xff) << 8 | (unsigned int)(*dst) & 0xff;
    return color;
}

void my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char *dst;
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;

	dst = data->addr + ((int)y * data->line_length + (int)x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int create_rgb (int red , int green, int blue)
{
    return (red << 16 | green << 8 | blue);
}
int get_argb(char *c,t_data *data)
{
    int i = 0;
    while(i < 2)
    {
        if(data->parsing->coloring[i].surface[0] == *c)
            return (create_rgb(data->parsing->coloring[i].rgb[0], data->parsing->coloring[i].rgb[1], data->parsing->coloring[i].rgb[2]));
            i++;
    }
    return (0);
}

void fill_bg(t_data *data)
{
    int y = 0;
    int x;
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

void cast_all_rays(t_data *data, t_map *map)
{
    double ray_angle = data->player->pangle - (FOV / 2);
    int i = 0;
    init_rays(data, &data->rays[0], ray_angle);
    while (i < num_of_rays)
    {
        horz_interception(data, i, map);
        vert_interception(data, i, map);
        hor_ver_distances(data, i);
        render3DWalls(data , i);
        i++;
    }
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
    int color = 0;
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
    double distProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
    double correctDistance = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player->pangle);
    double wallStripHeight = (TILE_SIZE / correctDistance) * distProjPlane;

    double starty = render_center - (wallStripHeight / 2);
    double endy = render_center + (wallStripHeight / 2);

    if (starty < 0) 
        starty = 0;
    if (endy > WINDOW_HEIGHT) 
        endy = WINDOW_HEIGHT;

    unsigned int wall_color;
    draw_strip(data, i, starty, endy, wallStripHeight);
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

bool collision(double x, double y ,t_map *map)
{
    int mapx = (int)(x / TILE_SIZE);
    int mapy = (int)(y / TILE_SIZE);
    
    if (x < 0 || y < 0 || x >= (map->x_len * TILE_SIZE) || y >= (map->y_len * TILE_SIZE))
        return true;
    if(map->map[mapy])
    {
        return (map->map && map->map[mapy][mapx] == 1);
    }
    return (0);
}

int update(t_data *data, t_map *map)
{
    double next_px = data->player->px;
    double next_py = data->player->py;

    data->player->pangle += normalize_angle(data->player->turn_direction * data->player->rotation_speed);

    int movestep = data->player->walk_direction * data->player->move_speed;
    int sidestep = data->player->sidewalk * data->player->move_speed;
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

    clear_window(data);
    fill_bg(data);
    cast_all_rays(data, map);

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

    return 0;
}

int keypress (int keycode, void *data)
{
    t_data *img = (t_data *)data; 
    
    if (keycode == 65307)
    {
        mlx_destroy_display(img->mlx);
        mlx_destroy_window(img->mlx, img->win);
        // free(img->win);
        // free(img->rays);
        // free(img->mlx);
        exit (0);
    }
    else if (keycode == RIGHT)
        img->player->sidewalk = 1;
    else if (keycode == LEFT)
        img->player->sidewalk = -1;
    else if(keycode == UP)
        img->player->walk_direction = 1;
    else if (keycode == DOWN)
        img->player->walk_direction = -1;
    else if (keycode == TURN_RIGHT) 
        img->player->turn_direction = 1;
    else if (keycode == TURN_LEFT)
        img->player->turn_direction = -1;
    update(img, img->parsing->map);
    return 0;
}

int keyrelease (int keycode, void *data)
{
    t_data *img = (t_data *)data; 

    img->player->sidewalk =0;
    img->player->walk_direction = 0;
    img->player->turn_direction = 0;

    update(img, img->parsing->map);
    return 0;
}

void init_player (t_player *player, t_map *map)
{
    player->px = map->x;
    player->py = map->y ;
    player->player_size = 11;
    player->pangle = map->n;
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->sidewalk = 0;
    player->move_speed = 15;
    player->rotation_speed = 4 * (PI / 180);
}

int	c(void *data)
{
    t_data *img = (t_data *)data;
    mlx_destroy_display(img->mlx);
    mlx_destroy_window(img->mlx, img->win);
    // free(img->win);
    // free(img->rays);
    // free(img->mlx);
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
int main (int ac, char **av)
{
    t_parsing *parser;

    parser = map_validation(file_validation(ac , av));
    int width, height;
    t_data *data = malloc(sizeof(t_data));
    t_player *player = malloc(sizeof (t_player));
    t_rays *rays = malloc (sizeof(t_rays) * (WINDOW_WIDTH / STRIP_WIDTH));
    t_texture *textures = malloc (sizeof(t_texture));
    data->parsing = parser;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    data->texture = textures;
    data->texture->north_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "NO"), &width, &height);
    data->texture->north_addr = mlx_get_data_addr(data->texture->north_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->south_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "SO"), &width, &height);
    data->texture->south_addr = mlx_get_data_addr(data->texture->south_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->east_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "EA") ,&width, &height);
    data->texture->east_addr = mlx_get_data_addr(data->texture->east_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    data->texture->west_img = mlx_xpm_file_to_image(data->mlx, get_texture(data, "WE"), &width, &height);
    data->texture->west_addr = mlx_get_data_addr(data->texture->west_img, &data->texture->bits_per_pixel, &data->texture->line_length, &data->texture->endian);
    fill_color_buffers(data);
    init_player (player, data->parsing->map);
    data->player = player;
    data->rays = rays;
    fill_bg(data);
    cast_all_rays(data , parser->map);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 02, (1L << 0), keypress, data);
    mlx_hook(data->win, 03, (1L << 1), keyrelease, data);
    mlx_hook(data->win, 17, 0, c, data);
    mlx_loop(data->mlx);
}
