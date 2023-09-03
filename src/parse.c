/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:57:25 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/03 21:33:30 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"



int	maxLength(t_list *head)
{
	int	max;

	max = 0;
	while (head)
	{
		if (max < (int) ft_strlen(head->content))
			max = ft_strlen(head->content);
		head = head->next;
	}
	return (max);
}

void	parseMap(t_data *data, t_list *head)
{
	int	i;
	int	j;

	data->map_num_rows = ft_lstsize(head);
	data->map_num_cols = maxLength(head);
	data->map = make2d(data->map_num_rows, data->map_num_cols);
	i = -1;
	while (++i < data->map_num_rows)
	{
		j = ft_strcpy(data->map[i], head->content);
		while (j < data->map_num_cols)
			data->map[i][j++] = ' ';
		head = head->next;
	}
}

int	isFirstMapLine(char *str)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '1')
			return (0);
		if (*(str++) == '1')
			flag = 1;
	}
	return (flag);
}

void	extractMap(t_data *data, t_list **head)
{
	t_list	*map;
	t_list	*info;

	if (!head || !(*head))
		return ;
	map = *head;
	info = *head;
	while (map && !isFirstMapLine(map->content))
		map = map->next;
	if (!map || map == info)
		ft_lstclear(head);
	else
	{
		while (info->next != map)
			info = info->next;
		info->next = NULL;
		if (!parseData(data, *head))
			ft_lstclear(head);
		else
			*head = map;
	}
}

int	parse(t_data *data, char *filename)
{
	int	fd;
	t_list *head;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("\x1B[31mCan't open '", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("'!\x1B[0m\n", 2);
		return (0);
	}
	head = readLines(fd);
	close(fd);
	extractMap(data, &head);
	if (!head)
		return (ft_putstr_fd("\x1B[31mError!\x1B[0m\n", 2), 0);
	parseMap(data, head);
	ft_lstclear(&head);
	if (!mapCheck(data))
		return (ft_putstr_fd("\x1B[31mError!\x1B[0m\n", 2), 0); //free stuff, map, textures, init
	return (1);
}
