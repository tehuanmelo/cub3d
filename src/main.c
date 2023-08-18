/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/18 10:16:27 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void setup(t_data *data)
{
    data->map = get_map();
    data->cealing_color = DARK_GREY;
    data->floor_color = LIGHT_GREY;
    data->textures = get_textures(data);

    
    data->mlx_ptr = mlx_init();
    data->mlx_win = NULL;
    data->map_num_rows = get_map_rows(data->map);
    data->map_num_cols = ft_strlen(data->map[0]);
    data->window_width = data->map_num_cols * TILE_SIZE;
    data->window_height = data->map_num_rows * TILE_SIZE;
    data->is_game_running = false;
    data->num_rays = data->window_width;
    data->player.width = 10;
    data->player.height = 10;
    data->player.walk_direction = 0;
    data->player.side_direction = 0;
    data->player.turn_direction = 0;
    data->rays = malloc(data->num_rays * sizeof(t_ray));
    data->color_buffer = malloc((data->window_width * data->window_height) * sizeof(int));
    get_player_position(data);
}

void update(t_data *data)
{
    move_player(data);
    cast_all_rays(data);
}

void render(t_data *data)
{
    mlx_clear_window(data->mlx_ptr, data->mlx_win);
    render_walls(data);
    render_map(data);
    render_player(data);
    render_ray(data);
    render_color_buffer(data);
}

int game_loop(t_data *data)
{
    if (!data->is_game_running)
        release_resources(data);
    update(data);
    render(data);
    return true;
}

int main()
{
    t_data data;
    
    setup(&data);
    data.is_game_running = initialize_window(&data);
    if (data.is_game_running)
    {
        mlx_loop_hook(data.mlx_ptr, game_loop, &data);
        mlx_hook(data.mlx_win, 2, 1L << 0, key_pressed, &data);
        mlx_hook(data.mlx_win, 3, 1L << 0, key_released, &data);
        mlx_hook(data.mlx_win, ON_DESTROY, 1L << 17, release_resources, &data);
        mlx_loop(data.mlx_ptr);
    }
    release_resources(&data);
    return 0;
}
