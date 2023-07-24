/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:03:36 by tde-melo          #+#    #+#             */
/*   Updated: 2022/07/25 15:03:17 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     s: The string from which to create the substring.
//     start: The start index of the substring in the
//     string ’s’.
// len:
//     The maximum length of the substring.
// Return value
//     The substring.
//     NULL if the allocation fails.
// External functs.
//     malloc
// Description
//     Allocates (with malloc(3)) and returns a substring
//     from the string ’s’.
//     The substring begins at index ’start’ and is of
//     maximum size ’len’.

#include "libft.h"

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
