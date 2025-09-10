/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:48 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 13:03:27 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strrchr.c
 * @brief returns a pointer to the last occurrence of
 the character c in the string s.
 */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char )c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char s[] = "tripouille";
// 	printf("%s\n", s);
// 	printf("%s\n", ft_strrchr(s, 't' + 256));
// }
