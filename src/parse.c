/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:57:25 by mgoltay           #+#    #+#             */
/*   Updated: 2023/08/30 21:17:57 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse(t_data *data, char *filename)
{
	// default tehuan map
	(void) filename;
	data->mlx_ptr = mlx_init();
	data->map = get_map();
	data->cealing_color = DARK_GREY;
	data->floor_color = LIGHT_GREY;
	data->textures = get_textures(data);
	data->map_num_rows = get_map_rows(data->map);
	data->map_num_cols = ft_strlen(data->map[0]);
	return (1);
}

// THINGS TO HANDLE:
// virus program to spread and see if player can walk out
// border to nearest 1, anything other than space?