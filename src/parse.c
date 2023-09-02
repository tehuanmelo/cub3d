/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:57:25 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/02 21:29:21 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_list	*readLines(int fd)
{
	t_list	*head;
	char	*str;
	int		i;

	str = get_next_line(fd);
	head = NULL;
	while (str)
	{
		i = -1;
		while (str[++i])
			if (str[i] == '\n')
				str[i] = '\0';
		ft_lstadd_back(&head, ft_lstnew(str));
		str = get_next_line(fd);
	}
	return (head);
}

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
	data->map = (char **) malloc(sizeof(char *) * (data->map_num_rows + 1));
	i = -1;
	while (++i < data->map_num_rows)
		data->map[i] = (char *) malloc(sizeof(char) * data->map_num_cols + 1);
	data->map[i] = NULL;
	i = -1;
	while (++i < data->map_num_rows)
	{
		j = ft_strcpy(data->map[i], head->content);
		while (j < data->map_num_cols)
			data->map[i][j++] = ' ';
		data->map[i][j] = '\0';
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

void	printlist(t_list *head)
{
	while (head)
	{
		ft_putstr_fd(head->content, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
	}
}

void	parseData(t_data *data, t_list *info)
{
	(void) data;
	(void) info;
}

void	extractMap(t_data *data, t_list **head)
{
	t_list	*map;
	t_list	*info;

	// default
	data->cealing_color = DARK_GREY;
	data->floor_color = LIGHT_GREY;
	data->mlx_ptr = mlx_init();
	data->textures = get_textures(data);

	map = *head;
	info = *head;
	while (map && !isFirstMapLine(map->content))
		map = map->next;
	if (!map)
		ft_lstclear(head);
	else if (map == info)
		return ;
	else
	{
		while (info->next != map)
			info = info->next;
		info->next = NULL;
		parseData(data, *head);
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
	if (!mapCheck(data))
		return (ft_putstr_fd("\x1B[31mError!\x1B[0m\n", 2), 0); //free stuff
	ft_lstclear(&head);
	return (1);
}
