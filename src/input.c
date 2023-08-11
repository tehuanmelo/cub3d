/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:36:59 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/12 00:37:10 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_pressed(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        data->is_game_running = false;
    else if (keycode == KEY_W || keycode == KEY_UP)
        data->player.walk_direction = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->player.walk_direction = -1;
    else if (keycode == KEY_A)
        data->player.side_direction = 1;
    else if (keycode == KEY_D)
        data->player.side_direction = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 1;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = -1;
    return EXIT_SUCCESS;
}

int key_released(int keycode, t_data *data)
{
    if (keycode == KEY_W || keycode == KEY_UP)
        data->player.walk_direction = 0;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->player.walk_direction = 0;
    else if (keycode == KEY_A)
        data->player.side_direction = 0;
    else if (keycode == KEY_D)
        data->player.side_direction = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 0;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = 0;
    return EXIT_SUCCESS;
}
