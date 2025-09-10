/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:44 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:33:56 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strjoin.c
 * @brief Allocates memory (using malloc(3)) and returns a
new string, which is the result of concatening ’s1’
and ’s2’.
 */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ptr;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j++];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*int main(void)
{
    char s1[] = "maria";
    char s2[] = " joao";
    char    *result = ft_strjoin(s1, s2);
    printf("%s\n", result);
	free(result);
}*/