/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:27 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 13:05:34 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strlcat.c
 * @brief appends the NUL-terminated string src to the end
 of dst. It will append at most size - strlen(dst) - 1 bytes,
 NUL-terminating the result.
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dest;

	i = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dst);
	if (size <= len_dest)
	{
		return (len_src + size);
	}
	while (src[i] && i < (size - len_dest - 1))
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_src + len_dest);
}
