/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:17:55 by mgoltay           #+#    #+#             */
/*   Updated: 2023/09/03 19:48:16 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (s1[i] != s2[i] || !(s1[i]) || !(s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return (&((char *)s)[len]);
		len--;
	}
	return (NULL);
}

int	ft_strcpy(char *dst, char *src)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		len = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = 0;
	return (substr);
}
