/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:28:35 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:33:33 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strtrim.c
 * @brief Allocates memory (using malloc(3)) and returns a
copy of ’s1’ with characters from ’set’ removed
from the beginning and the end.
 */

#include "libft.h"

static int	ft_count_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				start++;
				i++;
				j = 0;
			}
			else
				j++;
		}
		i++;
	}
	return (start);
}

static int	ft_count_end(char const *s1, char const *set, int size)
{
	int	i;
	int	j;
	int	end;

	j = 0;
	i = size - 1;
	end = 0;
	while (i > 0)
	{
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				end++;
				i--;
				j = 0;
			}
			else
				j++;
		}
		i--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	char	*ptr;
	int		size;
	int		end;

	if (!s1[0])
		return (ft_strdup(""));
	if (!set[0])
		return (ft_strdup(s1));
	size = ft_strlen(s1);
	start = ft_count_start(s1, set);
	end = 0;
	if (start < size)
		end = ft_count_end(s1, set, size);
	size = size - end - start;
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = s1[start++];
	ptr[i] = '\0';
	return (ptr);
}

/*int	main(void)
{
	char	s1[] = "   xxx   xxx";
	char	set[] = " x";
	char	*result = ft_strtrim(s1, set);
	printf("%s\n", result);
    free(result);
	return (0);
}*/