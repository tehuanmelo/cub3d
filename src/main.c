/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/30 21:18:10 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	setup(t_data *data)
{
	parse(data, "./map/map.cub");
	data->mlx_win = NULL;
	data->is_game_running = false;
	data->num_rays = WINDOW_WIDTH;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	data->player.turn_direction = 0;
	data->rays = malloc(data->num_rays * sizeof(t_ray));
	data->color_buffer = malloc((WINDOW_WIDTH * WINDOW_HEIGHT) * sizeof(int));
	get_player_position(data);
	init_buffer_image(data);
}

int	game_loop(t_data *data)
{
	if (!data->is_game_running)
		release_resources(data);
	
	//update
	move_player(data);
	cast_all_rays(data);
	
	//render
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	render_walls(data);
	render_map(data);
	render_player(data);
	render_ray(data);
	render_color_buffer(data);
	
	return (true);
}

void	handle_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx_win, 3, 1L << 0, key_released, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 1L << 17, release_resources, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("\x1B[31mIncorrect Number of Arguments!\x1B[0m\n", 2);
		return (1);
	}
	if (!parse(&data, argv[1]))
	{
		ft_putstr_fd("\x1B[31mError!\x1B[0m\n", 2);
		return (1);
	}
	setup(&data);
	data.is_game_running = initialize_window(&data);
	if (data.is_game_running)
		handle_hooks(&data);
	release_resources(&data);
	return (0);
}
