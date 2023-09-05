/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/09/05 18:41:16 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	setup(t_data *data)
{
	data->mlx_win = NULL;
	data->is_game_running = false;
	data->num_rays = WINDOW_WIDTH;
	data->mini_map_scale = map_scale_factor(data);
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
	move_player(data);
	cast_all_rays(data);
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
	mlx_hook(data->mlx_win, 6, 1L << 0, mouse_event, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 1L << 17, release_resources, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc > 2)
		return (ft_putstr_fd("\x1B[31mOnly One Argument Needed!\x1B[0m\n", 2), 1);
	if (argc < 2 || ft_strlen(argv[1]) < 4 
		|| ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
		return (ft_putstr_fd("\x1B[31mEnter .cub file!\x1B[0m\n", 2), 1);
	if (!parse(&data, argv[1]))
		return (1);
	setup(&data);
	data.is_game_running = initialize_window(&data);
	if (data.is_game_running)
		handle_hooks(&data);
	release_resources(&data);
	return (0);
}
