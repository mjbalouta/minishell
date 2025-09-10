/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:39 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 13:07:07 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strncmp.c
 * @brief strcmp() returns an integer indicating
 the result of the comparison, as follows: 0, if the s1
 and s2 are equal; a negative value if s1 is less than s2;
 a positive value if s1 is greater than s2.
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < (n - 1) && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

// int	main(void)
// {
// 	char s1[] = "zyxbcdefgh";
// 	char s2[] = "abcdwxyz";
// 	int result = ft_strncmp(s1, s2, 0);
// 	printf("%d\n", result);
// }
