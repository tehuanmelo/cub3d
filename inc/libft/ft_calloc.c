/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:17:25 by tehuanmelo        #+#    #+#             */
/*   Updated: 2022/08/01 15:57:04 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
**      The malloc(), calloc(), valloc(), realloc(), and reallocf()
**      functions allocate memory.  The allocated memory is aligned
**      such that it can be used for any data type, including
**      AltiVec- and SSE-related types.  The aligned_alloc()
**      function allocates memory with the requested alignment.
**      The free() function frees allocations that were created via
**      the preceding allocation functions.
** 
**      The calloc() function contiguously allocates enough space
**      for count objects that are size bytes of memory each and
**      returns a pointer to the allocated memory.  The allocated
**      memory is filled with bytes of value zero.
** 
** RETURN VALUES
**      If successful, calloc(), malloc(), realloc(), reallocf(),
**      valloc(), and aligned_alloc() functions return a pointer to
**      allocated memory.  If there is an error, they return a NULL
**      pointer and set errno to ENOMEM.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	new = malloc(count * size);
	if (!new)
		return (NULL);
	ft_bzero(new, count * size);
	return (new);
}
