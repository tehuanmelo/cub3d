/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:46:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:46:31 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int release_resources(t_data *data)
{
    int i;

    free(data->rays);
    free(data->color_buffer);
    i = 0;
    while (data->map[i])
        free(data->map[i++]);
    free(data->map);
    i = 0;
    while (i < 4)
        mlx_destroy_image(data->mlx_ptr, data->textures[i++].img);
    free(data->textures);
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    data->mlx_ptr = NULL;
    exit(EXIT_SUCCESS);
}