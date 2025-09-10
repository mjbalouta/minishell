/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:30:00 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:34:07 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_substr.c
 * @brief  allocates memory (using malloc(3)) and returns a
substring from the string ’s’.
The substring starts at index ’start’ and has a
maximum length of ’len’.
 */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*src;
	char	*ptr;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if ((size_t)start >= size)
		return (ft_strdup(""));
	src = (char *)s + start;
	size = ft_strlen(src);
	while (size > len)
		size--;
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, src, size + 1);
	return (ptr);
}
// int main(void)
// {
//     char const s[]= "maria";
//     char *result = ft_substr(s, 2, 10);
//     printf("%s\n", result);
//     return(0);
// }
