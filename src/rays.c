/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:51:35 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/18 15:02:56 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_colision get_horizontal_colision(t_data *data, t_ray_direction ray_direction, float ray_angle)
{
    t_colision colision;

    init_colision(&colision, true);
    colision.y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    if (ray_direction.is_ray_facing_down)
        colision.y_intercept += TILE_SIZE;
    colision.x_intercept = data->player.x + (colision.y_intercept - data->player.y) / tan(ray_angle);
    colision.y_step = TILE_SIZE;
    if (ray_direction.is_ray_facing_up)
        colision.y_step *= -1;
    colision.x_step = TILE_SIZE / tan(ray_angle);
    if (ray_direction.is_ray_facing_left && colision.x_step > 0)
        colision.x_step *= -1;
    if (ray_direction.is_ray_facing_right && colision.x_step < 0)
        colision.x_step *= -1;
    colision.next_x_intercept = colision.x_intercept;
    colision.next_y_intercept = colision.y_intercept;
    find_colision(data, &colision, ray_direction.is_ray_facing_up);
    return colision;
}

t_colision get_vertical_colision(t_data *data, t_ray_direction ray_direction, float ray_angle)
{
    t_colision colision;

    init_colision(&colision, false);
    colision.x_intercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    if (ray_direction.is_ray_facing_right)
        colision.x_intercept += TILE_SIZE;
    colision.y_intercept = data->player.y + (colision.x_intercept - data->player.x) * tan(ray_angle);
    colision.x_step = TILE_SIZE;
    if (ray_direction.is_ray_facing_left)
        colision.x_step *= -1;
    colision.y_step = TILE_SIZE * tan(ray_angle);
    if (ray_direction.is_ray_facing_up && colision.y_step > 0)
        colision.y_step *= -1;
    if (ray_direction.is_ray_facing_down && colision.y_step < 0)
        colision.y_step *= -1;
    colision.next_x_intercept = colision.x_intercept;
    colision.next_y_intercept = colision.y_intercept;
    find_colision(data, &colision, ray_direction.is_ray_facing_left);
    return colision;
}

void cast_ray(t_data *data, float ray_angle, int ray_id)
{
    t_colision horizontal;
    t_colision vertical;
    t_ray_direction ray_direction;
    
    ray_angle = clean_angle(ray_angle);
    ray_direction = get_ray_direction(ray_angle);
    horizontal = get_horizontal_colision(data, ray_direction, ray_angle);
    vertical = get_vertical_colision(data, ray_direction, ray_angle);
    if (vertical.hit_distance < horizontal.hit_distance)
    {
        data->rays[ray_id].distance = vertical.hit_distance;
        data->rays[ray_id].wall_hit_x = vertical.wall_hit_x;
        data->rays[ray_id].wall_hit_y = vertical.wall_hit_y;
        data->rays[ray_id].was_hit_vertical = true;
    }
    else
    {
        data->rays[ray_id].distance = horizontal.hit_distance;
        data->rays[ray_id].wall_hit_x = horizontal.wall_hit_x;
        data->rays[ray_id].wall_hit_y = horizontal.wall_hit_y;
        data->rays[ray_id].was_hit_vertical = false;
    }
    data->rays[ray_id].ray_angle = ray_angle;
    data->rays[ray_id].direction = ray_direction;
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
