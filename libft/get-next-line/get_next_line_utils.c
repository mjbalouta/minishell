/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:30 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/28 16:30:36 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_nstrlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_nstrjoin(char *s1, char *s2)
{
	int		size;
	char	*ptr;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	size = ft_nstrlen(s1) + ft_nstrlen(s2);
	ptr = (char *)ft_ncalloc((size + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		ptr[i++] = s2[j++];
	}
	if (s1)
		free(s1);
	return (ptr);
}

void	*ft_ncalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	char	*temp;

	i = 0;
	if (size != 0 && nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	temp = (char *)ptr;
	while (i < (nmemb * size))
	{
		temp[i] = '\0';
		i++;
	}
	return (ptr);
}

void	ft_clean_array(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ptr[i] = '\0';
		i++;
	}
}

void	ft_free_arrays(char *result, char *line)
{
	if (result)
	{
		free(result);
		result = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}
