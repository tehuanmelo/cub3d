/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/18 15:25:44 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_image *get_textures(t_data *data)
{
    t_image *textures;

    textures = malloc(sizeof(t_image) * 4);
    if (!textures)
        return NULL;
    textures[0] = create_image(data, "textures/BLUE-ROCK.xpm");
    textures[1] = create_image(data, "textures/BROWN-ROCK.xpm");
    textures[2] = create_image(data, "textures/SILVER-ROCK.xpm");
    textures[3] = create_image(data, "textures/MOSS-ROCK.xpm");

    return textures;
}

void render_walls(t_data *data)
{
    int x;
    int y;
    float corrected_ray_distance;
    float dist_projected_wall;
    int projected_wall_height;
    int top_pixel;
    int bottom_pixel;

    x = 0;
    while (x < data->num_rays)
    {
        dist_projected_wall = (data->window_width / 2) / tan(FOV_ANGLE / 2);
        // fixing the fish eye effect
        corrected_ray_distance = data->rays[x].distance * cos(data->player.rotation_angle - data->rays[x].ray_angle);

        projected_wall_height = (int)((TILE_SIZE / corrected_ray_distance * dist_projected_wall));
        top_pixel = (data->window_height / 2) - (projected_wall_height / 2);
        bottom_pixel = (data->window_height / 2) + (projected_wall_height / 2);

        if (top_pixel < 0)
            top_pixel = 0;
        if (bottom_pixel > data->window_height)
            bottom_pixel = data->window_height;

        // draw ceiling
        y = -1;
        while (++y < top_pixel)
            draw_pixel(data, x, y, data->cealing_color);

        int textureOffsetX;
        if (data->rays[x].was_hit_vertical)
            textureOffsetX = (int)data->rays[x].wall_hit_y % TILE_SIZE;
        else
            textureOffsetX = (int)data->rays[x].wall_hit_x % TILE_SIZE;

        // render the wall from wallTopPixel to wallBottomPixel
        y = top_pixel;
        while (y < bottom_pixel)
        {
            int distanceFromTop = y + (projected_wall_height / 2) - (data->window_height / 2); // allows the top pixel be negative and prevent distortion
            int textureOffsetY = distanceFromTop * ((float)TILE_SIZE / projected_wall_height); //

            // set the color of the wall based on the color from the texture
            int orientation = 0;
            if (!data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_up)
                orientation = 0;
            else if (!data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_down)
                orientation = 1;
            else if (data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_left)
                orientation = 2;
            else if (data->rays[x].was_hit_vertical && data->rays[x].direction.is_ray_facing_right)
                orientation = 3;

            int texelColor = my_mlx_pixel_get(&data->textures[orientation], textureOffsetX, textureOffsetY);
            draw_pixel(data, x, y, texelColor);
            y++;
        }

        // draw floor
        y = bottom_pixel - 1;
        while (++y < data->window_height)
            draw_pixel(data, x, y, data->floor_color);

        x++;
    }
}
