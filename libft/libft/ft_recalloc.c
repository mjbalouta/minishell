/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:29:18 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/06/02 13:51:26 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_recalloc.c
 * @brief frees previous memory and reallocates memory for an array of
 * nmemb elements of size bytes each and returns a pointer to the
 * allocated memory.
 */
#include "libft.h"

void	*ft_recalloc(void *ptr, size_t old_size, size_t nmemb, size_t size)
{
	void	*new_ptr;
	size_t	new_size;
	size_t	copy_len;

	if (size != 0 && nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	new_size = nmemb * size;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr && old_size > 0)
	{
		copy_len = old_size;
		if (old_size > new_size)
			copy_len = new_size;
		ft_memcpy(new_ptr, ptr, copy_len);
	}
	if (old_size < (nmemb * size))
		ft_bzero((char *)new_ptr + old_size, (nmemb * size) - old_size);
	free(ptr);
	return (new_ptr);
}
