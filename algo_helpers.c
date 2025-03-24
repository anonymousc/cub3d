#include "Wolf3D.h"

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void process_hor_interception (t_data *data, t_map *map, int i, double nexthortouchX, double nexthortouchY)
{
    while (nexthortouchX >= 0 && nexthortouchX <= (map->x_len * TILE_SIZE) && nexthortouchY >= 0 && nexthortouchY <= (map->y_len * TILE_SIZE))
    {
        if (collision(nexthortouchX, (nexthortouchY - data->rays[i].rayfacingUP), map))
        {
            data->rays[i].foundhorwallhit = true;
            data->rays[i].horwallhitX = nexthortouchX;
            data->rays[i].horwallhitY = nexthortouchY;
            break;
        }
        else
        {
            nexthortouchX += data->rays[i].xstep;
            nexthortouchY += data->rays[i].ystep;
        }
    }
}

void process_vert_interception (t_data *data, t_map *map, int i, double nextverttouchX, double nextverttouchY)
{
    while (nextverttouchX >= 0 && nextverttouchX <= (map->x_len * TILE_SIZE) && nextverttouchY >= 0 && nextverttouchY <= (map->y_len * TILE_SIZE))
    {
        if (collision((nextverttouchX - data->rays[i].rayfacingLEFT ), nextverttouchY, map))
        {
            data->rays[i].foundvertwallhit = true;
            data->rays[i].vertwallhitX = nextverttouchX;
            data->rays[i].vertwallhitY = nextverttouchY;
            break;
        }
        else
        {
            nextverttouchX += data->rays[i].xstep;
            nextverttouchY += data->rays[i].ystep;
        }
    }
}