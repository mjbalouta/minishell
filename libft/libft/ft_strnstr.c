/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:43 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 13:07:48 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strnstr.c
 * @brief locates the first occurrence of the null-terminated
 string little in the string big, where not more than len
 characters are searched.
 */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i] == little[j] && (i < len) && big[i] && little[j])
		{
			i++;
			j++;
		}
		if (!little[j])
			return ((char *)&big[i - j]);
		i = i - j + 1;
	}
	return (0);
}

// int	main(void)
// {
// 	const char big[] = "oh no not the empty string !";
// 	const char little[] = "";
// 	char *result;
// 	result = ft_strnstr(big, little, 0);
// 	if (result == 0)
// 		printf("0\n");
// 	else
// 		printf("%s\n", result);
// }
