/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:58:50 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:52:52 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int initialize_window(t_data *data)
{
    data->mlx_win = mlx_new_window(data->mlx_ptr, data->window_width, data->window_height, "Cub3d");
    if (!data->mlx_ptr || !data->mlx_win)
    {
        perror("Could not initialize the window");
        return false;
    }
    return true;
}

void clear_color_buffer(t_data *data, int color)
{
    int i;

    i = 0;
    while (i < data->window_width * data->window_height)
    {
        data->color_buffer[i] = color;
        i++;
    }
}



void init_buffer_image(t_data *data)
{
    data->buffer_image.img = mlx_new_image(data->mlx_ptr, data->window_width, data->window_height);
    data->buffer_image.addr = mlx_get_data_addr(data->buffer_image.img, &data->buffer_image.bits_per_pixel, &data->buffer_image.line_length, &data->buffer_image.endian);
}


void render_color_buffer(t_data *data)
{
    int x;
    int y;

    init_buffer_image(data);
    x = 0;
    while (x < data->window_width)
    {
        y = 0;
        while (y < data->window_height)
        {
            my_mlx_pixel_put(&data->buffer_image, x, y, data->color_buffer[(data->window_width * y) + x]);
            y++;
        }
        x++;
    }
    clear_color_buffer(data, 0x000000);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->buffer_image.img, 0, 0);
    if (data->buffer_image.img)
        mlx_destroy_image(data->mlx_ptr, data->buffer_image.img);
}
