/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:00 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 12:59:42 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_memcmp.c
 * @brief returns an integer less than, equal to, or
 greater than zero if the first n bytes of s1 is found,
 respectively, to be less than, to match, or be greater
 than the first n bytes of s2.
 */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;
	size_t				i;

	i = 0;
	ptr_s1 = (const unsigned char *)s1;
	ptr_s2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ptr_s1[i] == ptr_s2[i] && i < (n - 1))
	{
		i++;
	}
	return (ptr_s1[i] - ptr_s2[i]);
}

/*int	main(void)
{
	printf("%d\n", ft_memcmp("abc", "abc", 2));    // 0 (iguais)
	printf("%d\n", ft_memcmp("abc", "abd", 3));    // -1 ('c' - 'd')
	printf("%d\n", ft_memcmp("hello", "hellz", 4)); 
	// 0 (iguais até o 4º caractere)
	printf("%d\n", ft_memcmp("hello", "hellz", 5)); // -11 ('o' - 'z')
	printf("%d\n", ft_memcmp("abc", "abcd", 5));  // -100 ('\0' - 'd')
	printf("%d\n", ft_memcmp("abcd", "abc", 5));  // 100 ('d' - '\0')
	printf("%d\n", ft_memcmp("a", "abc", 1));     // 0 (comparou só 'a')
	printf("%d\n", ft_memcmp("abc", "a", 2));     // positivo ('b' - '\0')
	printf("%d\n", ft_memcmp("abc", "abc", 0));   // 0 (n == 0, sem comparação)	
}*/
