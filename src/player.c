/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:31:03 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/09/05 15:47:52 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_rotation_angle(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'N')
		data->player.rotation_angle = 271 * (PI / 180);
	else if (data->map[i][j] == 'S')
		data->player.rotation_angle = 91 * (PI / 180);
	else if (data->map[i][j] == 'E')
		data->player.rotation_angle = 1 * (PI / 180);
	else if (data->map[i][j] == 'W')
		data->player.rotation_angle = 181 * (PI / 180);
}

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' 
				&& data->map[i][j] != ' ')
			{
				get_rotation_angle(data, i, j);
				data->player.x = (j * TILE_SIZE) + TILE_SIZE / 2;
				data->player.y = (i * TILE_SIZE) + TILE_SIZE / 2;
				return ;
			}
		}
	}
}

void	move_player(t_data *data)
{
	float	move_step;
	float	side_move_step;
	float	side_angle;
	float	new_player_x;
	float	new_player_y;

	new_player_x = data->player.x;
	new_player_y = data->player.y;
	move_step = data->player.walk_direction * WALK_SPEED;
	side_move_step = data->player.side_direction * WALK_SPEED;
	data->player.rotation_angle += data->player.turn_direction * 
		(TURN_SPEED * (PI / 180));
	side_angle = data->player.rotation_angle - (PI / 2);
	new_player_x += cos(data->player.rotation_angle) * move_step;
	new_player_y += sin(data->player.rotation_angle) * move_step;
	new_player_x += cos(side_angle) * side_move_step;
	new_player_y += sin(side_angle) * side_move_step;
	if (!is_wall_at(data, new_player_x, new_player_y))
	{
		data->player.x = new_player_x;
		data->player.y = new_player_y;
	}
}

void	render_player(t_data *data)
{
	t_rect	rect;

	rect.x = (data->player.x * data->mini_map_scale) - PLAYER_WIDTH / 2;
	rect.y = (data->player.y * data->mini_map_scale) - PLAYER_HEIGHT / 2;
	rect.height = PLAYER_HEIGHT;
	rect.width = PLAYER_WIDTH;
	rect.color = RED;
	draw_rect(data, rect);
}
