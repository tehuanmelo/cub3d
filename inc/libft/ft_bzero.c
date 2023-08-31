/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:05:34 by tde-melo          #+#    #+#             */
/*   Updated: 2023/08/30 21:02:04 by mgoltay          ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		write(fd, s++, 1);
}
