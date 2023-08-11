/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:52:00 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:52:57 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_pixel(t_data *data, int x, int y, int color)
{
    data->color_buffer[(data->window_width * y) + x] = color;
}

void draw_rect (t_data *data, int x, int y, int width, int height, int color)
{
    int i;
    int j;
    
    i = x;
    while (i < x + width)
    {
        j = y;
        while (j < y + height)
        {
            draw_pixel(data, i, j, color);
            j++;
        }
        i++;
    }
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(&data->buffer_image, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
