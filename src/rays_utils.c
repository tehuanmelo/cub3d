/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:55:37 by tde-melo          #+#    #+#             */
/*   Updated: 2023/08/22 18:51:49 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// clean angle returns a positive angle e.g -3 % 360 = 357 degrees
// remainder function replaces modulus to returns a float
float	clean_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	get_hit_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0))));
}

t_ray_direction	get_ray_direction(float ray_angle)
{
	t_ray_direction	ray_direction;

	ray_direction.is_ray_facing_up = ray_angle > PI && ray_angle < TWO_PI;
	ray_direction.is_ray_facing_down = !ray_direction.is_ray_facing_up;
	ray_direction.is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5
		* PI;
	ray_direction.is_ray_facing_left = !ray_direction.is_ray_facing_right;
	return (ray_direction);
}

void	init_colision(t_colision *colision, bool is_horizontal)
{
	colision->found_wall_hit = false;
	colision->wall_hit_x = 0;
	colision->wall_hit_y = 0;
	colision->hit_distance = INT_MAX;
	colision->is_horizontal = is_horizontal;
}

void	find_colision(t_data *data, t_colision *colision, bool direction)
{
	while (is_inside_map(data, colision->next_x_intercept,
			colision->next_y_intercept))
	{
		colision->check_x = colision->next_x_intercept;
		colision->check_y = colision->next_y_intercept;
		if (direction && !colision->is_horizontal)
			colision->check_x--;
		if (direction && colision->is_horizontal)
			colision->check_y--;
		if (is_wall_at(data, colision->check_x, colision->check_y))
		{
			colision->wall_hit_x = colision->next_x_intercept;
			colision->wall_hit_y = colision->next_y_intercept;
			colision->found_wall_hit = true;
			break ;
		}
		else
		{
			colision->next_x_intercept += colision->x_step;
			colision->next_y_intercept += colision->y_step;
		}
	}
	if (colision->found_wall_hit)
		colision->hit_distance = get_hit_distance(data->player.x,
				data->player.y, colision->wall_hit_x, colision->wall_hit_y);
}
