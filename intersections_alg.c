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

int horz_interception (t_data *data, int i)
{
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    double nexthortouchX;
    double nexthortouchY;

    yintercept = (int)(data->player->py / TILE_SIZE) * TILE_SIZE;
    yintercept += (data->rays[i].rayfacingDOWN ? TILE_SIZE : 0);
    xintercept = data->player->px + ((yintercept - data->player->py) / tan(data->rays[i].ray_angle));

    ystep = TILE_SIZE;
    ystep *= data->rays[i].rayfacingUP ? -1 : 1;
    xstep = TILE_SIZE / tan(data->rays[i].ray_angle);
    xstep *= (data->rays[i].rayfacingLEFT && xstep > 0) ? -1 : 1;
    xstep *= (data->rays[i].rayfacingRIGHT && xstep < 0) ? -1 : 1;
    nexthortouchX = xintercept;
    nexthortouchY = yintercept;
    while (nexthortouchX >= 0 && nexthortouchX <= (MAP_X * TILE_SIZE) && nexthortouchY >= 0 && nexthortouchY <= (MAP_X * TILE_SIZE))
    {
        if (collision(nexthortouchX, (nexthortouchY - data->rays[i].rayfacingUP)))
        {
            data->rays[i].foundhorwallhit = true;
            data->rays[i].horwallhitX = nexthortouchX;
            data->rays[i].horwallhitY = nexthortouchY;
            break;
        }
        else
        {
            nexthortouchX += xstep;
            nexthortouchY += ystep;
        }
    }
    return 0;
}

int vert_interception (t_data *data, int i)
{
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    double nextverttouchX;
    double nextverttouchY;

    xintercept = (int)(data->player->px / TILE_SIZE) * TILE_SIZE;
    xintercept += data->rays[i].rayfacingRIGHT ? TILE_SIZE : 0;
    yintercept = data->player->py + ((xintercept - data->player->px) * tan(data->rays[i].ray_angle));

    xstep = TILE_SIZE;
    xstep *= data->rays[i].rayfacingLEFT ? -1 : 1;
    ystep = TILE_SIZE * tan(data->rays[i].ray_angle);
    ystep *= (data->rays[i].rayfacingUP && ystep > 0) ? -1 : 1;
    ystep *= (data->rays[i].rayfacingDOWN && ystep < 0) ? -1 : 1;
    nextverttouchX = xintercept;
    nextverttouchY = yintercept;
    while (nextverttouchX >= 0 && nextverttouchX <= (MAP_X * TILE_SIZE) && nextverttouchY >= 0 && nextverttouchY <= (MAP_X * TILE_SIZE))
    {
        if (collision((nextverttouchX - data->rays[i].rayfacingLEFT), nextverttouchY))
        {
            data->rays[i].foundvertwallhit = true;
            data->rays[i].vertwallhitX = nextverttouchX;
            data->rays[i].vertwallhitY = nextverttouchY;
            break;
        }
        else
        {
            nextverttouchX += xstep;
            nextverttouchY += ystep;
        }
    }
    
    return 0;
}

void hor_ver_distances (t_data *data, int i)
{
    if (data->rays[i].foundhorwallhit)
        data->rays[i].HorzDistance = distance(data->player->px, data->player->py, data->rays[i].horwallhitX, data->rays[i].horwallhitY);
    else 
        data->rays[i].HorzDistance = LLONG_MAX;
    if (data->rays[i].foundvertwallhit)
        data->rays[i].VertDistance = distance(data->player->px, data->player->py, data->rays[i].vertwallhitX, data->rays[i].vertwallhitY);
    else    
        data->rays[i].VertDistance = LLONG_MAX;
    if (data->rays[i].HorzDistance < data->rays[i].VertDistance)
    {
        data->rays[i].WallHitX = data->rays[i].horwallhitX;
        data->rays[i].WallHitY = data->rays[i].horwallhitY;
        data->rays[i].distance = data->rays[i].HorzDistance;
    }
    else
    {
        data->rays[i].WallHitX = data->rays[i].vertwallhitX;
        data->rays[i].WallHitY = data->rays[i].vertwallhitY;
        data->rays[i].distance = data->rays[i].VertDistance;  
    }
    data->rays[i].washitvertical = (data->rays[i].VertDistance < data->rays[i].HorzDistance);
}
