/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:51:35 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:27:26 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// clean angle returns a positive angle e.g -3 % 360 = 357 degrees
// remainder function replaces modulus to returns a float
float clean_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle;
}

float get_hit_distance(float x0, float y0, float x1, float y1)
{
    return sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
}

void cast_ray(t_data *data, float ray_angle, int ray_id)
{
    ray_angle = clean_angle(ray_angle);

    int isRayFacingUp = ray_angle > PI && ray_angle < TWO_PI;
    int isRayFacingDown = !isRayFacingUp;

    int isRayFacingRight = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = data->player.x + (yintercept - data->player.y) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray_angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (is_inside_map(data, nextHorzTouchX, nextHorzTouchY))
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY;
        if (isRayFacingUp)
            yToCheck--;

        if (is_wall_at(data, xToCheck, yToCheck))
        {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // not using horzWallContent maybe can delete it
            horzWallContent = data->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = data->player.y + (xintercept - data->player.x) * tan(ray_angle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(ray_angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (is_inside_map(data, nextVertTouchX, nextVertTouchY))
    {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (is_wall_at(data, xToCheck, yToCheck))
        {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            // not using vertWallContent maybe can delete it
            vertWallContent = data->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    float horzHitDistance = foundHorzWallHit
                                ? get_hit_distance(data->player.x, data->player.y, horzWallHitX, horzWallHitY)
                                : INT_MAX;
    float vertHitDistance = foundVertWallHit
                                ? get_hit_distance(data->player.x, data->player.y, vertWallHitX, vertWallHitY)
                                : INT_MAX;

    if (vertHitDistance < horzHitDistance)
    {
        data->rays[ray_id].distance = vertHitDistance;
        data->rays[ray_id].wall_hit_x = vertWallHitX;
        data->rays[ray_id].wall_hit_y = vertWallHitY;
        // not using wall_hit_content maybe can delete it
        data->rays[ray_id].wall_hit_content = vertWallContent;
        data->rays[ray_id].was_hit_vertical = true;
    }
    else
    {
        data->rays[ray_id].distance = horzHitDistance;
        data->rays[ray_id].wall_hit_x = horzWallHitX;
        data->rays[ray_id].wall_hit_y = horzWallHitY;
        // not using wall_hit_content maybe can delete it
        data->rays[ray_id].wall_hit_content = horzWallContent;
        data->rays[ray_id].was_hit_vertical = false;
    }
    data->rays[ray_id].ray_angle = ray_angle;
    data->rays[ray_id].is_ray_facing_down = isRayFacingDown;
    data->rays[ray_id].is_ray_facing_up = isRayFacingUp;
    data->rays[ray_id].is_ray_facing_left = isRayFacingLeft;
    data->rays[ray_id].is_ray_facing_right = isRayFacingRight;
}

void cast_all_rays(t_data *data)
{
    float ray_angle;
    int i;

    // we start casting the rays from left to right, the first ray is the actual player angle minus the half of field of view
    ray_angle = data->player.rotation_angle - (FOV_ANGLE / 2);
    i = 0;
    while (i < data->num_rays)
    {
        cast_ray(data, ray_angle, i);
        // update the ray_angle to the next angle, FOV divided by the number of rays
        // if FOV is 60 and we need 800 rays. we increment the angle in 0.075
        ray_angle += FOV_ANGLE / data->num_rays;
        i++;
    }
}

void render_ray(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_rays)
    {
        draw_line(
            data,
            data->player.x * MINI_MAP_SCALE,
            data->player.y * MINI_MAP_SCALE,
            data->rays[i].wall_hit_x * MINI_MAP_SCALE,
            data->rays[i].wall_hit_y * MINI_MAP_SCALE,
            RED);
        i++;
    }
}
