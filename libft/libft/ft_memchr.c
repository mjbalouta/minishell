/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:29:55 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 12:58:30 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_memchr.c
 * @brief scans the initial n bytes of the memory
 area pointed to by s for the first instance of c.
 Both c and the bytes of the memory area pointed to
 by s are  interpreted as unsigned char.
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < ((unsigned char)n))
	{
		if (ptr[i] == (unsigned char)c)
		{
			return (ptr + i);
		}
		i++;
	}
	return (0);
}
