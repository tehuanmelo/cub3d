/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:12:23 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:42:35 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int my_mlx_pixel_get(t_image *img, int x, int y)
{
    int color;
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    color = *(unsigned int *)dst;
    return color;
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_image create_image(t_data *data, char *image_path)
{
    t_image img;
    img.width = 64;
    img.height = 64;
    img.img = mlx_xpm_file_to_image(data->mlx_ptr, image_path, &img.width, &img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    return (img);
}