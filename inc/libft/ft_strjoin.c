/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:24:54 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/05 12:01:22 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//      s1: The prefix string.
//      s2: The suffix string.
// Return value
//      The new string.
//      NULL if the allocation fails.
// External functs.
//      malloc
// Description
//      Allocates (with malloc(3)) and returns a new
//      string, which is the result of the concatenation
//      of ’s1’ and ’s2’.

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	length;
	int		i;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = 0;
	}
	length = ft_strlen(s1) + ft_strlen(s2);
	new = malloc((length + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (*s2)
		new[i++] = *s2++;
	new[i] = 0;
	free(s1);
	return (new);
}
