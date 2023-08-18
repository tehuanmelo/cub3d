/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/18 21:59:34 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_image *get_textures(t_data *data)
{
    t_image *textures;
    char *north;
    char *south;
    char *east;
    char *west;
    
    north = "textures/RED-BRICK.xpm";
    south = "textures/MOSS-ROCK.xpm";
    east = "textures/SILVER-ROCK.xpm";
    west = "textures/BLUE-ROCK.xpm";
    textures = malloc(sizeof(t_image) * 4);
    if (!textures)
        return NULL;
    textures[0] = create_image(data, north);
    textures[1] = create_image(data, south);
    textures[2] = create_image(data, east);
    textures[3] = create_image(data, west);
    return textures;
}

void draw_cealing(t_data *data, t_wall wall, int x)
{
    int y;
    
    y = 0;
    while (y < wall.top_pixel)
    {
        draw_pixel(data, x, y, data->cealing_color);
        y++;
    }
}

void draw_floor(t_data *data, t_wall wall, int x)
{
    int y;
    
    y = wall.bottom_pixel;
    while (y < data->window_height)
    {
        draw_pixel(data, x, y, data->floor_color);
        y++;
    }
}

void init_wall(t_data *data, t_wall *wall, int x)
{
    wall->projected_wall_dist = (data->window_width / 2) / tan(FOV_ANGLE / 2);
    // fixing the fish eye effect
    wall->corrected_ray_distance = data->rays[x].distance * cos(data->player.rotation_angle - data->rays[x].ray_angle);
    wall->projected_wall_height = (int)((TILE_SIZE / wall->corrected_ray_distance * wall->projected_wall_dist));
    wall->top_pixel = (data->window_height / 2) - (wall->projected_wall_height / 2);
    wall->bottom_pixel = (data->window_height / 2) + (wall->projected_wall_height / 2);
    if (wall->top_pixel < 0)
        wall->top_pixel = 0;
    if (wall->bottom_pixel > data->window_height)
        wall->bottom_pixel = data->window_height;
    if (data->rays[x].was_hit_vertical)
            wall->x_texture_offset = (int)data->rays[x].wall_hit_y % TILE_SIZE;
        else
            wall->x_texture_offset = (int)data->rays[x].wall_hit_x % TILE_SIZE;
}

void draw_wall(t_data *data, t_wall wall, int x)
{
    int y;
        
    y = wall.top_pixel;
    while (y < wall.bottom_pixel)
    {
        wall.distance_from_top = y + (wall.projected_wall_height / 2) - (data->window_height / 2); // allows the top pixel be negative and prevent distortion
        wall.y_texture_offset = wall.distance_from_top * ((float)TILE_SIZE / wall.projected_wall_height); //
        if (!data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_up)
            wall.orientation = 0;
        else if (!data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_down)
            wall.orientation = 1;
        else if (data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_left)
            wall.orientation = 2;
        else if (data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_right)
            wall.orientation = 3;
        int texelColor = my_mlx_pixel_get(&data->textures[wall.orientation], wall.x_texture_offset, wall.y_texture_offset);
        draw_pixel(data, x, y, texelColor);
        y++;
    }
}

void render_walls(t_data *data)
{
    int x;
    t_wall wall;

    x = 0;
    while (x < data->num_rays)
    {
        init_wall(data, &wall, x);
        draw_cealing(data, wall, x);
        draw_wall(data, wall, x);
        draw_floor(data, wall, x);
        x++;
    }
}
