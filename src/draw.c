/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:52:00 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/30 19:08:00 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_pixel(t_data *data, int x, int y, int color)
{
	data->color_buffer[(WINDOW_WIDTH * y) + x] = color;
}

void	draw_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	i = rect.x - 1;
	while (++i < rect.x + rect.width)
	{
		j = rect.y - 1;
		while (++j < rect.y + rect.height)
			draw_pixel(data, i, j, rect.color);
	}
}

int	get_side_step(int delta_x, int delta_y)
{
	if (abs(delta_x) >= abs(delta_y))
		return (abs(delta_x));
	else
		return (abs(delta_y));
}

void	draw_line(t_data *data, t_line line)
{
	int	i;

	line.delta_x = (line.x1 - line.x0);
	line.delta_y = (line.y1 - line.y0);
	line.side_step = get_side_step(line.delta_x, line.delta_y);
	line.current_x = line.x0;
	line.current_y = line.y0;
	line.inc_x = line.delta_x / (float)line.side_step;
	line.inc_y = line.delta_y / (float)line.side_step;
	i = -1;
	while (++i < line.side_step)
	{
		draw_pixel(data, round(line.current_x), round(line.current_y),
			line.color);
		line.current_x += line.inc_x;
		line.current_y += line.inc_y;
	}
}
