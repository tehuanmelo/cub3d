/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:01:42 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/04 22:14:49 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// NO, SO, WE, EA, F, C
int	indexinfo(char *str)
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

void	cleanspaces(char *str)
{
	int	i;

	if (!str || !str[0])
		return ;
	while (isin(str[0], " \t"))
		removestart(str);
	while (str[0] && isin(str[ft_strlen(str) - 1], " \t"))
		removestart(&str[ft_strlen(str) - 1]);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (isin(str[i + 1], " \t"))
				removestart(&str[i + 1]);
			break ;
		}
	}
	if (indexinfo(str) == 4 || indexinfo(str) == 5)
		while (str[++i])
			if (isin(str[i], " \t"))
				removestart(&str[i]);
}

void	cleanlist(t_list **head)
{
	t_list	*info;

	if (!head || !(*head))
		return ;
	while (isemptyline((*head)->content))
		delone(head);
	info = *head;
	while (info && info->next)
	{
		while (info && info->next && isemptyline(info->next->content))
			delone(&info->next);
		cleanspaces(info->content);
		info = info->next;
	}
}

int	isvalid(char *strinfo[6], t_list *info)
{
	int		index;

	if (ft_lstsize(info) != 6)
		return (0);
	index = -1;
	while (++index < 6)
		strinfo[index] = NULL;
	while (info)
	{
		index = indexinfo(info->content);
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

int	parsedata(t_data *data, t_list *info)
{
	char	*strinfo[6];

	cleanlist(&info);
	if (!info || !isvalid(strinfo, info) || !putdata(data, strinfo))
		return (0);
	return (ft_lstclear(&info), 1);
}
