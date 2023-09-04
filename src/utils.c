/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:04:59 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/04 22:06:21 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**make2d(int rows, int cols)
{
	char	**strs;
	int		i;
	int		j;

	strs = (char **) malloc(sizeof(char *) * (rows + 1));
	i = -1;
	while (++i < rows)
	{
		strs[i] = (char *) malloc(sizeof(char) * (cols + 1));
		j = -1;
		while (++j <= cols)
			strs[i][j] = 0;
	}
	strs[i] = NULL;
	return (strs);
}

void	free2d(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

t_list	*readlines(int fd)
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

int	isemptyline(char *str)
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

void	stopcorner(t_data *data, char **checked)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->map_num_rows)
	{
		y = -1;
		while (++y < data->map_num_cols)
			if (data->map[x][y] == '0' && !checked[x][y])
				data->map[x][y] = ' ';
	}
}
