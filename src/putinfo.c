/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:47:56 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/05 20:54:32 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	removestart(char *str)
{
	int	i;

	if (!str || !str[0])
		return ;
	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

int	ft_atoi_len(char *str, int *i)
{
	int	num;

	if (!str || !i)
		return (-1);
	num = 0;
	while (str[*i] && str[*i] != ',')
	{
		if (str[*i] < '0' || str[*i] > '9')
			return (-1);
		num = num * 10 + (str[(*i)++] - '0');
	}
	if (num > 255)
		return (-1);
	return (num);
}

int	parsecolor(char *str)
{
	int	colour;
	int	num;
	int	i;

	if (ft_strlen(str) > 11)
		return (-1);
	colour = 0;
	i = 0;
	num = ft_atoi_len(str, &i);
	if (num == -1 || str[i++] != ',')
		return (-1);
	colour = num;
	num = ft_atoi_len(str, &i);
	if (num == -1 || str[i++] != ',')
		return (-1);
	colour = 256 * colour + num;
	num = ft_atoi_len(str, &i);
	if (num == -1 || str[i++] != '\0')
		return (-1);
	colour = 256 * colour + num;
	return (colour);
}

int	checkdata(char *strinfo[6])
{
	int	fd[4];
	int	i;

	if (parsecolor(&strinfo[4][2]) == -1 || parsecolor(&strinfo[5][2]) == -1)
		return (0);
	i = -1;
	while (++i < 4)
		if (ft_strlen(strinfo[i]) < 4 || ft_strcmp(&strinfo[i][ft_strlen(strinfo[i]) - 4], ".xpm"))
			return (0);
	i = -1;
	while (++i < 4)
		fd[i] = open(&strinfo[i][3], O_RDONLY);
	i = -1;
	while (++i < 4)
		if (fd[i] != -1)
			close(fd[i]);
	i = -1;
	while (++i < 4)
		if (fd[i] == -1)
			return (0);
	return (1);
}

// NO, SO, WE, EA, F, C
int	putdata(t_data *data, char *strinfo[6])
{
	int	i;

	if (!checkdata(strinfo))
		return (0);
	data->floor_color = parsecolor(&strinfo[4][2]);
	data->cealing_color = parsecolor(&strinfo[5][2]);
	data->textures = malloc(sizeof(t_image) * 4);
	if (!data->textures)
		return (0);
	data->mlx_ptr = mlx_init();
	i = -1;
	while (++i < 4)
	{
		data->textures[i] = create_image(data, &strinfo[i][3]);
		if (!data->textures[i].img)
			return (free(data->textures), 0);
	}
	return (1);
}
