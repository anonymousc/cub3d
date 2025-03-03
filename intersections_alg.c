#include "Wolf3D.h"

// float normalize_angle(float angle)
// {
//     angle = fmod(angle, 2 * PI);
//     if (angle < 0)
//         angle += 2 * PI;
//     return angle;
// }
// float distance(float x1, float y1, float x2, float y2)
// {
//     return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
// }

// int horz_interception (t_data *data, int i)
// {
//     float xintercept;
//     int yintercept;
//     float xstep;
//     float ystep;
//     float nexthortouchX;
//     float nexthortouchY;

//     yintercept = (int)(data->player->py / TILE_SIZE) * TILE_SIZE + (data->rays[i].rayfacingDOWN ? TILE_SIZE : 0);
//     xintercept = data->player->px + ((yintercept - data->player->py) / tan(data->rays[i].ray_angle));

//     ystep = TILE_SIZE;
//     if (data->rays[i].rayfacingUP)
//         ystep *= -1;
//     xstep = ystep / tan(data->rays[i].ray_angle);
//     if (data->rays[i].rayfacingLEFT && xstep > 0)
//         xstep *= -1;
//     if (data->rays[i].rayfacingRIGHT && xstep < 0)
//         xstep *= -1;
//     nexthortouchX = xintercept;
//     nexthortouchY = yintercept;
//     while (nexthortouchX >= 0 && nexthortouchX <= WINDOW_WIDTH && nexthortouchY >= 0 && nexthortouchY <= WINDOW_HEIGHT)
//     {
//         if (collision(nexthortouchX, (nexthortouchY - data->rays[i].rayfacingUP)))
//         {
//             data->rays[i].foundhorwallhit = true;
//             data->rays[i].horwallhitX = nexthortouchX;
//             data->rays[i].horwallhitY = nexthortouchY;
//             break;
//         }
//         else
//         {
//             nexthortouchX += xstep;
//             nexthortouchY += ystep;
//         }
//     }
//     return 0;
// }

// int vert_interception (t_data *data, int i)
// {
//     int xintercept;
//     float yintercept;
//     float xstep;
//     float ystep;
//     float nextverttouchX;
//     float nextverttouchY;

//     xintercept = (int)(data->player->px / TILE_SIZE) * TILE_SIZE + (data->rays[i].rayfacingRIGHT ? TILE_SIZE : 0);
//     yintercept = data->player->py + ((xintercept - data->player->px) * tan(data->rays[i].ray_angle));

//     xstep = TILE_SIZE;
//     if (data->rays[i].rayfacingLEFT)
//         xstep *= -1;
//     ystep = xstep * tan(data->rays[i].ray_angle);
//     if (data->rays[i].rayfacingUP && ystep > 0)
//         ystep *= -1;
//     if (data->rays[i].rayfacingDOWN && ystep < 0)
//         ystep *= -1;
//     nextverttouchX = xintercept;
//     nextverttouchY = yintercept;
//     while (nextverttouchX >= 0 && nextverttouchX <= WINDOW_WIDTH && nextverttouchY >= 0 && nextverttouchY <= WINDOW_HEIGHT)
//     {
//         if (collision((nextverttouchX - data->rays[i].rayfacingLEFT), nextverttouchY))
//         {
//             data->rays[i].foundvertwallhit = true;
//             data->rays[i].vertwallhitX = nextverttouchX;
//             data->rays[i].vertwallhitY = nextverttouchY;
//             break;
//         }
//         else
//         {
//             nextverttouchX += xstep;
//             nextverttouchY += ystep;
//         }
//     }
    
//     return 0;
// }

// void hor_ver_distances (t_data *data, int i)
// {
//     if (data->rays[i].foundhorwallhit)
//         data->rays[i].HorzDistance = distance(data->player->px, data->player->py, data->rays[i].horwallhitX, data->rays[i].horwallhitY);
//     else 
//         data->rays[i].HorzDistance = LLONG_MAX;
//     if (data->rays[i].foundvertwallhit)
//         data->rays[i].VertDistance = distance(data->player->px, data->player->py, data->rays[i].vertwallhitX, data->rays[i].vertwallhitY);
//     else    
//         data->rays[i].VertDistance = LLONG_MAX;
//     data->rays[i].washitvertical = (data->rays[i].VertDistance < data->rays[i].HorzDistance);
//     if (data->rays[i].HorzDistance < data->rays[i].VertDistance)
//     {
//         data->rays[i].WallHitX = data->rays[i].horwallhitX;
//         data->rays[i].WallHitY = data->rays[i].horwallhitY;
//         data->rays[i].distance = data->rays[i].HorzDistance;
//     }
//     else
//     {
//         data->rays[i].WallHitX = data->rays[i].vertwallhitX;
//         data->rays[i].WallHitY = data->rays[i].vertwallhitY;
//         data->rays[i].distance = data->rays[i].VertDistance;  
//     }
// }
