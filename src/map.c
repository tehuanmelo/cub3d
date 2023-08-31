/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:28:23 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/30 19:16:43 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**get_map(void)
{
	int		fd;
	char	*buffer;
	char	character;
	int		flag;
	int		i;
	char	**map;

	fd = open("map/map.cub", O_RDONLY);
	buffer = malloc(100000 * sizeof(char));
	i = 0;
	while ((flag = read(fd, &character, 1)) > 0)
		buffer[i++] = character;
	buffer[i] = 0;
	if (flag == -1 || i == 0)
		return (free(buffer), NULL);
	map = ft_split(buffer, '\n');
	if (map == NULL)
		return (free(buffer), NULL);
	free(buffer);
	close(fd);
	return (map);
}

int	get_map_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

bool	is_wall_at(t_data *data, float x, float y)
{
	int	map_grid_x;
	int	map_grid_y;

	if (!is_inside_map(data, x, y))
		return (true);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	return (data->map[map_grid_y][map_grid_x] == '1'
		|| data->map[map_grid_y][map_grid_x] == ' ');
}

void	render_map(t_data *data)
{
	t_rect	rect;
	int		i;
	int		j;

	i = -1;
	while (++i < data->map_num_rows)
	{
		j = -1;
		while (++j < data->map_num_cols)
		{
			rect.x = (j * TILE_SIZE) * MINI_MAP_SCALE;
			rect.y = (i * TILE_SIZE) * MINI_MAP_SCALE;
			rect.height = TILE_SIZE * MINI_MAP_SCALE;
			rect.width = TILE_SIZE * MINI_MAP_SCALE;
			if (data->map[i][j] == '1')
				rect.color = WHITE;
			else
				rect.color = BLACK;
			draw_rect(data, rect);
		}
	}
}

bool	is_inside_map(t_data *data, float x, float y)
{
	return (x >= 0 && x < data->map_num_cols * TILE_SIZE && y >= 0
		&& y < data->map_num_rows * TILE_SIZE);
}
