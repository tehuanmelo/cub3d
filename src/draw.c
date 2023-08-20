/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:52:00 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/20 20:22:31 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_pixel(t_data *data, int x, int y, int color)
{
    data->color_buffer[(WINDOW_WIDTH * y) + x] = color;
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

int get_side_step(int delta_x, int delta_y)
{
    int side_step;
    
    if (abs(delta_x) >= abs(delta_y))
        side_step = abs(delta_x);
    else    
        side_step = abs(delta_y);
    return side_step;
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int delta_x;
    int delta_y;
    int side_step;
    float current_x;
    float current_y;
    float inc_x;
    float inc_y;
    int i;

    delta_x = (x1 - x0);
    delta_y = (y1 - y0);
    side_step = get_side_step(delta_x, delta_y);
    current_x = x0;
    current_y = y0;
    inc_x = delta_x / (float)side_step;
    inc_y = delta_y / (float)side_step;
    i = -1;
    while (++i < side_step)
    {
        draw_pixel(data, round(current_x), round(current_y), color);
        current_x += inc_x;
        current_y += inc_y;
    }
}
