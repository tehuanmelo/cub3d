/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:20:42 by tehuanmelo        #+#    #+#             */
/*   Updated: 2022/12/31 12:49:38 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words(char const *s, char c)
{
	int	counter;

	counter = 0;
	if (!*s)
		return (0);
	if (*s == c)
		s++;
	while (*s)
	{
		if (*s == c || (*s != c && (*(s + 1)) == 0))
			counter++;
		s++;
	}
	return (counter);
}

int	ft_strlensplt(char const *s, char c)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		if ((*s == c && (*(s - 1)) != c) || (*s != c && (*(s + 1)) == 0)
			|| (*s != c && (*(s + 1)) == c))
		{
			counter++;
			return (counter);
		}
		counter++;
		s++;
	}
	return (counter);
}

void	freememory(char **str)
{
	char	**new;
	int		len;
	int		i;

	new = str;
	len = 0;
	while (*new++)
		len++;
	i = 0;
	while (i < len)
		free(str[i++]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		strwords;
	int		wlen;
	int		i;

	if (!s)
		return (NULL);
	strwords = ft_words(s, c);
	new = ft_calloc(ft_words(s, c) + 1, (sizeof(char *)));
	if (!new)
		return (NULL);
	i = 0;
	while (i < strwords)
	{
		while (*s == c)
			s++;
		wlen = ft_strlensplt(s, c);
		new[i] = ft_substr(s, 0, wlen);
		if (!new[i])
			freememory(new);
		s += wlen;
		i++;
	}
	return (new);
}
