#include "Wolf3D.h"

int horz_interception (t_data *data, int i , t_map *map)
{
    double xintercept;
    double yintercept;
    double nexthortouchX;
    double nexthortouchY;

    yintercept = (int)(data->player->py / TILE_SIZE) * TILE_SIZE;
    if (data->rays[i].rayfacingDOWN)
        yintercept += TILE_SIZE;
    xintercept = data->player->px + ((yintercept - data->player->py) / tan(data->rays[i].ray_angle));

    data->rays[i].ystep = TILE_SIZE;
    if (data->rays[i].rayfacingUP)
        data->rays[i].ystep *= -1;
    data->rays[i].xstep = TILE_SIZE / tan(data->rays[i].ray_angle);
    if (data->rays[i].rayfacingLEFT && data->rays[i].xstep > 0)
        data->rays[i].xstep *= -1;
    if (data->rays[i].rayfacingRIGHT && data->rays[i].xstep < 0)
        data->rays[i].xstep *= -1;
    nexthortouchX = xintercept;
    nexthortouchY = yintercept;
    
    process_hor_interception(data, map, i, nexthortouchX, nexthortouchY);
    return 0;
}

int vert_interception (t_data *data, int i, t_map *map)
{
    double xintercept;
    double yintercept;
    double nextverttouchX;
    double nextverttouchY;

    xintercept = (int)(data->player->px / TILE_SIZE) * TILE_SIZE;
    if (data->rays[i].rayfacingRIGHT)
        xintercept += TILE_SIZE;
    yintercept = data->player->py + ((xintercept - data->player->px) * tan(data->rays[i].ray_angle));

    data->rays[i].xstep = TILE_SIZE;
    if(data->rays[i].rayfacingLEFT)
        data->rays[i].xstep *= -1;
    data->rays[i].ystep = TILE_SIZE * tan(data->rays[i].ray_angle);
    if(data->rays[i].rayfacingUP && data->rays[i].ystep > 0)
        data->rays[i].ystep *= -1;
    if(data->rays[i].rayfacingDOWN && data->rays[i].ystep < 0)
        data->rays[i].ystep *= -1;
    nextverttouchX = xintercept;
    nextverttouchY = yintercept;
    
    process_vert_interception (data, map, i, nextverttouchX, nextverttouchY);
    
    return 0;
}

void hor_ver_distances (t_data *data, int i)
{
    if (data->rays[i].foundhorwallhit)
        data->rays[i].HorzDistance = distance(data->player->px, data->player->py, data->rays[i].horwallhitX, data->rays[i].horwallhitY);
    else 
        data->rays[i].HorzDistance = INT_MAX;
    if (data->rays[i].foundvertwallhit)
        data->rays[i].VertDistance = distance(data->player->px, data->player->py, data->rays[i].vertwallhitX, data->rays[i].vertwallhitY);
    else    
        data->rays[i].VertDistance = INT_MAX;
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
