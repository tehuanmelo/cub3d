/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:29:15 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/04 22:08:26 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	recursion(t_data *data, char **checked, int x, int y)
{
	int	flag;

	if (x < 0 || x >= data->map_num_rows || y < 0 || y >= data->map_num_cols)
		return (0);
	checked[x][y] = 1;
	if (data->map[x][y] == '1')
		return (1);
	if (x == 0 || x == data->map_num_rows - 1 
		|| y == 0 || y == data->map_num_cols - 1)
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

int	floodfill(t_data *data)
{
	int		x;
	int		y;
	char	**checked;
	int		flag;

	x = -1;
	while (++x < data->map_num_rows)
	{
		y = -1;
		while (++y < data->map_num_cols)
			if (isin(data->map[x][y], "NSEW"))
				break ;
		if (y != data->map_num_cols)
			break ;
	}
	checked = make2d(data->map_num_rows, data->map_num_cols);
	flag = recursion(data, checked, x, y);
	stopcorner(data, checked);
	free2d(checked);
	return (flag);
}

int	recurse(t_data *data, char **checked, int x, int y)
{
	int	flag;

	checked[x][y] = 1;
	if (data->map[x][y] == '1')
		return (1);
	if (data->map[x][y] != ' ')
		return (0);
	flag = 1;
	if (x > 0 && !checked[x - 1][y])
		flag = flag && recurse(data, checked, x - 1, y);
	if (x < data->map_num_rows - 1 && !checked[x + 1][y])
		flag = flag && recurse(data, checked, x + 1, y);
	if (y > 0 && !checked[x][y - 1])
		flag = flag && recurse(data, checked, x, y - 1);
	if (y < data->map_num_cols - 1 && !checked[x][y + 1])
		flag = flag && recurse(data, checked, x, y + 1);
	return (flag);
}

int	issurrounded(t_data *data)
{
	int		r;
	int		c;
	int		i;
	char	**checked;

	r = data->map_num_rows;
	c = data->map_num_cols;
	i = -1;
	checked = make2d(r, c);
	while (++i < data->map_num_rows)
		if ((!checked[i][0] && !recurse(data, checked, i, 0)) 
			|| (!checked[i][c - 1] && !recurse(data, checked, i, c - 1)))
			return (free2d(checked), 0);
	i = -1;
	while (++i < data->map_num_cols)
		if ((!checked[0][i] && !recurse(data, checked, 0, i)) 
			|| (!checked[r - 1][i] && !recurse(data, checked, r - 1, i)))
			return (free2d(checked), 0);
	free2d(checked);
	return (1);
}

int	charcheck(t_data *data)
{
	int	i;
	int	j;
	int	playercount;

	playercount = 0;
	i = -1;
	while (++i < data->map_num_rows)
	{
		j = -1;
		while (++j < data->map_num_cols)
		{
			if (!isin(data->map[i][j], "01NSEW X"))
				return (0);
			if (isin(data->map[i][j], "NSEW"))
				playercount++;
		}
	}
	return (playercount == 1);
}
