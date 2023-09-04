/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:29:15 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/04 18:05:45 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// if space is anywhere near something thats not a 1, error
int	checkSpace(t_data *data)
{
	int i;
	int	j;
	
	i = -1;
	while (++i < data->map_num_rows)
	{
		j = -1;
		while (++j < data->map_num_cols)
		{
			if (isIn(data->map[i][j], "0NSEW"))
			{
				if (i + 1 < data->map_num_rows && data->map[i + 1][j] == ' ')
					return (0);
				if (i - 1 >= 0 && data->map[i - 1][j] == ' ')
					return (0);
				if (j + 1 < data->map_num_cols && data->map[i][j + 1] == ' ')
					return (0);
				if (j - 1 >= 0 && data->map[i][j - 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

int	recursion(t_data *data, char **checked, int x, int y)
{
	int	flag;

	if (x < 0 || x >= data->map_num_rows || y < 0 || y >= data->map_num_cols)
		return (0);
	checked[x][y] = 1;
	if (data->map[x][y] == '1')
		return (1);
	if (x == 0 || x == data->map_num_rows - 1 || y == 0 || y == data->map_num_cols - 1)
		return (0);
	flag = 1;
	if (data->map[x][y] == ' ')
		data->map[x][y] = '1';
	if (!checked[x - 1][y])
		flag = flag && recursion(data, checked, x - 1, y);
	if (!checked[x + 1][y])
		flag = flag && recursion(data, checked, x + 1, y);
	if (!checked[x][y - 1])
		flag = flag && recursion(data, checked, x, y - 1);
	if (!checked[x][y + 1])
		flag = flag && recursion(data, checked, x, y + 1);
	return (flag);
}

int	floodFill(t_data *data)
{
	int	x;
	int	y;
	char	**checked;
	int	flag;

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
	checked = make2d(data->map_num_rows, data->map_num_cols);
	flag = recursion(data, checked, x, y);
	free2d(checked);
	return (flag);
}

int	isSurroundedR(t_data *data)
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
	return (1);
}

int	isSurrounded(t_data *data)
{
	int	i;
	int	j;

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
	return (1 && isSurroundedR(data));
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
