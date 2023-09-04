/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:04:59 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/04 17:54:05 by mgoltay          ###   ########.fr       */
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

int	isIn(char c, char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*(str++) == c)
			return (1);
	return (0);
}

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



// delete these two before submission
void	printlist(t_list *head)
{
	if (!head)
		ft_putstr_fd("EMPTYLIST\n", 1);
	while (head)
	{
		ft_putstr_fd(head->content, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
	}
}

void	printMap(t_data *data)
{
	for (int i = 0; i < data->map_num_rows; i++)
	{
		for (int j = 0; j < data->map_num_cols; j++)
			write(1, &data->map[i][j], 1);
		ft_putstr_fd("\n", 1);
	}		
}