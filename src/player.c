/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:31:03 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/22 16:07:30 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void get_player_position(t_data *data)
{
    int i;
    int j;

    i = -1;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] != '0' && data->map[i][j] != '1')
            {
                if (data->map[i][j] == 'N')
                    data->player.rotation_angle = 271 * (PI / 180);
                else if (data->map[i][j] == 'S')
                    data->player.rotation_angle = 91 * (PI / 180);
                else if (data->map[i][j] == 'E')
                    data->player.rotation_angle = 1;
                else if (data->map[i][j] == 'W')
                    data->player.rotation_angle = 181 * (PI / 180);
                data->player.x = (j * TILE_SIZE) + 32;
                data->player.y = (i * TILE_SIZE) + 32;
                return;
            }
        }
    }
}

void move_player(t_data *data)
{
    float move_step;
    float side_move_step;
    float side_angle;
    float new_player_x;
    float new_player_y;

    new_player_x = data->player.x;
    new_player_y = data->player.y;

    // the distance we want to move, 1 forward or -1 backward from walk_direction
    // WALK_SPEED is the number of pixels the player will move
    move_step = data->player.walk_direction * WALK_SPEED;
    side_move_step = data->player.side_direction * WALK_SPEED;

    // increment or decrement the player angle based on the turn_direction
    // times TURN_SPEED. How many angles we want to move
    data->player.rotation_angle += data->player.turn_direction * TURN_SPEED;
    side_angle = data->player.rotation_angle - (PI / 2);

    // Basic trigonometry to find the new coordinates
    // move step being the hypotenuse, new_player_x adjacent, new_player_y oposite
    new_player_x += cos(data->player.rotation_angle) * move_step;
    new_player_y += sin(data->player.rotation_angle) * move_step;

    new_player_x += cos(side_angle) * side_move_step;
    new_player_y += sin(side_angle) * side_move_step;

    // check if there is a wall in the new coordinates
    if (!is_wall_at(data, new_player_x, new_player_y))
    {
        data->player.x = new_player_x;
        data->player.y = new_player_y;
    }
}

void render_player(t_data *data)
{

    draw_rect(
        data,
        (data->player.x - 20) * MINI_MAP_SCALE,
        (data->player.y - 20) * MINI_MAP_SCALE,
        (int)PLAYER_WIDTH,
        (int)PLAYER_HEIGHT,
        RED
    );
}