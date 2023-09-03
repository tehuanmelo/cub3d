/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:01:42 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/03 21:33:15 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	isEmptyLine(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
	return (1);
}

void	delOne(t_list **ptr)
{
	t_list *temp;

	if (!ptr || !(*ptr))
		return ;
	temp = *ptr;
	*ptr = temp->next;
	if (temp && temp->content)
		free(temp->content);
	if (temp)
		free(temp);
}

void	removeStart(char *str)
{
	int	i;

	if (!str || !str[0])
		return ;
	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

// NO, SO, WE, EA, F, C
int	indexInfo(char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (0);
	else if (!ft_strncmp(str, "SO ", 3))
		return (1);
	else if (!ft_strncmp(str, "WE ", 3))
		return (2);
	else if (!ft_strncmp(str, "EA ", 3))
		return (3);
	else if (!ft_strncmp(str, "F ", 2))
		return (4);
	else if (!ft_strncmp(str, "C ", 2))
		return (5);
	return (-1);
}

void	cleanSpaces(char *str)
{
	int	i;

	if (!str || !str[0])
		return ;
	while (isIn(str[0], " \t"))
		removeStart(str);
	while (str[0] && isIn(str[ft_strlen(str) - 1], " \t"))
		removeStart(&str[ft_strlen(str) - 1]);
	i = -1;
	while (str[++i])
		if (str[i] == ' ')
		{
			while (isIn(str[i + 1], " \t"))
				removeStart(&str[i + 1]);
			break ;
		}
	if (indexInfo(str) == 4 || indexInfo(str) == 5)
		while (str[++i])
			if (isIn(str[i], " \t"))
				removeStart(&str[i]);
}

void	cleanList(t_list **head)
{
	t_list *info;

	if (!head || !(*head))
		return ;
	while (isEmptyLine((*head)->content))
		delOne(head);
	info = *head;
	while (info && info->next)
	{
		while (info && info->next && isEmptyLine(info->next->content))
			delOne(&info->next);
		cleanSpaces(info->content);
		info = info->next;
	}
}

int	isValid(t_data *data, t_list *info)
{
	char	*strinfo[6];
	int		index;
	
	(void) data; // store into array and see if empty or double

	if (ft_lstsize(info) < 6)
		return (0);
	index = -1;
	while (++index < 6)
		strinfo[index] = NULL;
	while (info)
	{
		index = indexInfo(info->content);
		if (index == -1)
			return (0);
		if (strinfo[index] != NULL)
			return (0);
		else
			strinfo[index] = info->content;
		info = info->next;
	}
	index = -1;
	while (++index < 6)
		if (strinfo[index] == NULL)
			return (0);
	return (1);
}

int	parseData(t_data *data, t_list *info)
{
	// char	*strinfo[6];

	cleanList(&info);
	if (!info)
		return (0);
	if (!isValid(data, info))
		return (0);
	ft_lstclear(&info);
	data->cealing_color = DARK_GREY;
	data->floor_color = LIGHT_GREY;
	data->mlx_ptr = mlx_init();
	data->textures = get_textures(data);
	return (1);
}
