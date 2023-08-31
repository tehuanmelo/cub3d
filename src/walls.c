/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/30 19:23:01 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_cealing(t_data *data, t_wall wall, int x)
{
	int	y;

	y = -1;
	while (++y < wall.top_pixel)
		draw_pixel(data, x, y, data->cealing_color);
}

void	draw_floor(t_data *data, t_wall wall, int x)
{
	int	y;

	y = wall.bottom_pixel - 1;
	while (++y < WINDOW_HEIGHT)
		draw_pixel(data, x, y, data->floor_color);
}

void	init_wall(t_data *data, t_wall *wall, int x)
{
	wall->projected_wall_dist = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	wall->corrected_ray_distance = data->rays[x].distance
		* cos(data->player.rotation_angle - data->rays[x].ray_angle);
	wall->projected_wall_height = (int)((TILE_SIZE
				/ wall->corrected_ray_distance * wall->projected_wall_dist));
	wall->top_pixel = (WINDOW_HEIGHT / 2) - (wall->projected_wall_height / 2);
	wall->bottom_pixel = (WINDOW_HEIGHT / 2) + (wall->projected_wall_height
			/ 2);
	if (wall->top_pixel < 0)
		wall->top_pixel = 0;
	if (wall->bottom_pixel > WINDOW_HEIGHT)
		wall->bottom_pixel = WINDOW_HEIGHT;
	if (data->rays[x].was_hit_vertical)
		wall->x_texture_offset = (int)data->rays[x].wall_hit_y % TILE_SIZE;
	else
		wall->x_texture_offset = (int)data->rays[x].wall_hit_x % TILE_SIZE;
}

void	draw_wall(t_data *data, t_wall wall, int x)
{
	int	y;

	y = wall.top_pixel - 1;
	while (++y < wall.bottom_pixel)
	{
		wall.distance_from_top = y + 
			(wall.projected_wall_height / 2) - (WINDOW_HEIGHT / 2);
		wall.y_texture_offset = wall.distance_from_top * ((float)TILE_SIZE
				/ wall.projected_wall_height);
		if (!data->rays[x].was_hit_vertical
			&& data->rays[x].direction.is_ray_facing_up)
			wall.orientation = 1;
		else if (!data->rays[x].was_hit_vertical
			&& data->rays[x].direction.is_ray_facing_down)
			wall.orientation = 0;
		else if (data->rays[x].was_hit_vertical
			&& data->rays[x].direction.is_ray_facing_left)
			wall.orientation = 3;
		else if (data->rays[x].was_hit_vertical
			&& data->rays[x].direction.is_ray_facing_right)
			wall.orientation = 2;
		wall.texel_color = my_mlx_pixel_get(&data->textures[wall.orientation],
				wall.x_texture_offset, wall.y_texture_offset);
		draw_pixel(data, x, y, wall.texel_color);
	}
}

void	render_walls(t_data *data)
{
	int		x;
	t_wall	wall;

	x = -1;
	while (++x < data->num_rays)
	{
		init_wall(data, &wall, x);
		draw_cealing(data, wall, x);
		draw_wall(data, wall, x);
		draw_floor(data, wall, x);
	}
}
