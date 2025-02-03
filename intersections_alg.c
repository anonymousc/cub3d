#include "wolf.h"

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}
int horz_interception (t_data *data, int i)
{
    float xintercept;
    int yintercept;
    float xstep;
    float ystep;
    float nexthortouchX;
    float nexthortouchY;

    yintercept = (int)(data->player->py / TILE_SIZE) * TILE_SIZE + TILE_SIZE * (data->rays[i].rayfacingDOWN);
    xintercept = data->player->px + ((yintercept - data->player->py) / tan(data->rays[i].ray_angle));

    ystep = TILE_SIZE;
    if (data->rays[i].rayfacingUP)
        ystep *= -1;
    xstep = ystep / tan(data->rays[i].ray_angle);
    if (data->rays[i].rayfacingLEFT && xstep > 0)
        xstep *= -1;
    if (data->rays[i].rayfacingRIGHT && xstep < 0)
        xstep *= -1;
    nexthortouchX = xintercept;
    nexthortouchY = yintercept;
    if (data->rays[i].rayfacingUP)
        nexthortouchY--;
    while (nexthortouchX >= 0 && nexthortouchX <= WINDOW_WIDTH && nexthortouchY >= 0 && nexthortouchY <= WINDOW_HEIGHT)
    {
        if (collision(nexthortouchX, nexthortouchY))
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
    float xintercept;
    int yintercept;
    float xstep;
    float ystep;
    float nextverttouchX;
    float nextverttouchY;

    xintercept = (int)(data->player->px / TILE_SIZE) * TILE_SIZE + TILE_SIZE * (data->rays[i].rayfacingRIGHT);
    yintercept = data->player->py + ((xintercept - data->player->px) * tan(data->rays[i].ray_angle));

    xstep = TILE_SIZE;
    if (data->rays[i].rayfacingLEFT)
        xstep *= -1;
    ystep = xstep * tan(data->rays[i].ray_angle);
    if (data->rays[i].rayfacingUP && ystep > 0)
        ystep *= -1;
    if (data->rays[i].rayfacingDOWN && ystep < 0)
        ystep *= -1;
    nextverttouchX = xintercept;
    nextverttouchY = yintercept;
    if (data->rays[i].rayfacingLEFT)
        nextverttouchX--;
    while (nextverttouchX >= 0 && nextverttouchX <= WINDOW_WIDTH && nextverttouchY >= 0 && nextverttouchY <= WINDOW_HEIGHT)
    {
        if (collision(nextverttouchX, nextverttouchY))
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
