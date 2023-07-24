/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:05:34 by tde-melo          #+#    #+#             */
/*   Updated: 2022/07/18 12:45:09 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The ft_bzero() function writes n zeroed bytes to the string s.
//      If n is zero, bzero() does nothing.

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = 0;
}
