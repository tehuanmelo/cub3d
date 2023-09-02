/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:29:15 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/02 21:57:16 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	isIn(char c, char *str)
{
	int	i;

	if (!str)
		return (0);
	while (*str)
		if (*(str++) == c)
			return (1);
	return (0);
}

// 4way check, stops at boundaries
// checks for 1, if so check = true, dont recurse


int	recursion(t_data *data, char **checked, int x, int y)
{
	if (data->map[x][y] == ' ')
		return (0);
	if (x + 1 < data->map_num_rows && !checked[x + 1][y])
	{
		if (data->map[x + 1][y] )
		return (recursion)
	}
	return (1);
}

int	floodFill(t_data *data)
{
	int	i;
	int	x;
	int	y;
	char **checked;

	checked = (char **) malloc(sizeof(char *) * data->map_num_rows);
	i = -1;
	while (++i < data->map_num_rows)
		checked[i] = (char *) malloc(sizeof(char) * data->map_num_cols);
	ft_bzero(checked, data->map_num_rows * data->map_num_cols);
	x = -1;
	while (++x < data->map_num_rows)
	{
		y = -1;
		while (++y < data->map_num_cols)
			if (isIn(data->map[x][y], "NSEW"))
				break;
		if (y != data->map_num_cols)
			break ;
	}
	checked[x][y] = 1;
	return (recursion(data, checked, x, y));
}

int	isSurrounded(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_num_rows)
	{
		j = 0;
		while (j < data->map_num_cols && data->map[i][j] != '1')
			if (data->map[i][j++] != ' ')
				return (0);
		j = data->map_num_cols - 1;
		while (j >= 0 && data->map[i][j] != '1')
			if (data->map[i][j--] != ' ')
				return (0);
	}
	j = -1;
	while (++j < data->map_num_cols)
	{
		i = 0;
		while (i < data->map_num_rows && data->map[i][j] != '1')
			if (data->map[i++][j] != ' ')
				return (0);
		i = data->map_num_rows - 1;
		while (i >= 0 && data->map[i][j] != '1')
			if (data->map[i--][j] != ' ')
				return (0);
	}
	return (1);
}

int	charCheck(t_data *data)
{
	int	i;
	int	j;
	int playercount;

	playercount = 0;
	i = -1;
	while (++i < data->map_num_rows)
	{
		j = -1;
		while (++j < data->map_num_cols)
		{
			if (!isIn(data->map[i][j], "01NSEW X"))
				return (0);
			if (isIn(data->map[i][j], "NSEW"))
				playercount++;
		}
	}
	return (playercount == 1);
}

int	mapCheck(t_data *data)
{
	if (!(charCheck(data) && isSurrounded(data) && floodFill(data)))
		return (0);
	return (1);
}

// checks:
// one player only
// virus program to spread and see if player can walk out
// border to nearest 1, anything other than space?