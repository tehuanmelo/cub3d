/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:28:23 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/11 19:59:47 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char **get_map(void)
{
    int fd = open("map/map.cub", O_RDONLY);
    char *buffer = malloc(100000 * sizeof(char));
    char character;
    int flag;
    int i = 0;

    while ((flag = read(fd, &character, 1)) > 0)
        buffer[i++] = character;
    buffer[i] = 0;
    if (flag == -1 || i == 0)
        return free(buffer), NULL;

    char **map = ft_split(buffer, '\n');
    if (map == NULL)
        return free(buffer), NULL;
    free(buffer);
    return map;
}

int get_map_rows(char **map)
{
    int rows = 0;
    while (*map++)
        rows++;
    return rows;
}

bool is_wall_at(t_data *data, float x, float y)
{
    int map_grid_x;
    int map_grid_y;

    // if x and y coordinates are out of boundaries returns true and do not move the player
    if ((x < 0 || x >= data->window_width) || (y < 0 || y >= data->window_height))
        return true;

    // divide the coordinate by the tile size to find the position in the map array.
    // round it down to get an integer value
    map_grid_x = floor(x / TILE_SIZE);
    map_grid_y = floor(y / TILE_SIZE);

    return data->map[map_grid_y][map_grid_x] == '1';
}


void render_map(t_data *data)
{
    int tile_x;
    int tile_y;
    int tile_color;
    int i;
    int j;

    i = 0;
    while (i < data->map_num_rows)
    {
        j = 0;
        while (j < data->map_num_cols)
        {
            tile_x = j * TILE_SIZE;
            tile_y = i * TILE_SIZE;
            if (data->map[i][j] == '1')
                tile_color = WHITE;
            else
                tile_color = BLACK;
            draw_rect(data, tile_x * MINI_MAP_SCALE, tile_y * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, tile_color);
            j++;
        }
        i++;
    }
}

bool is_inside_map(t_data *data, float x, float y)
{
    return (x >= 0 && x <= data->window_width && y >= 0 && y <= data->window_height);
}
