/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:43:53 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/21 09:45:18 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_split.c
 * @brief Allocates memory (using malloc(3)) and returns an
array of strings obtained by splitting ’s’ using
the character ’c’ as a delimiter. The array must
end with a NULL pointer.
 */
#include "libft.h"

static char	**ft_free_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	count = 0;
	word = 1;
	while (s[i])
	{
		if (word == 1 && s[i] != c)
			count++;
		word = 0;
		if (s[i] == c)
			word = 1;
		i++;
	}
	return (count);
}

static int	ft_count_char(int i, const char *s, char c)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_fill_array(char **array, int nr_words, const char *s, char c)
{
	int	j;
	int	i;
	int	start;
	int	count;

	j = 0;
	i = 0;
	while (j < nr_words)
	{
		count = 0;
		if (s[i] != c)
		{
			start = i;
			count = ft_count_char(i, s, c);
			array[j] = (char *)malloc(sizeof(char) * (count + 1));
			if (!array[j])
				return (ft_free_array(array));
			ft_strlcpy(array[j++], s + start, count + 1);
		}
		else
			i++;
		i = i + count;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		nr_words;

	nr_words = ft_count_words(s, c);
	array = (char **)ft_calloc((nr_words + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[nr_words] = NULL;
	array = ft_fill_array(array, nr_words, s, c);
	return (array);
}

/*int	main(void)
{
	char	s[] = " a+maria++joao++joao";
	char	c = '+';
	int		i = 0;
	char **result = ft_split(s, c);
	while (result[i])
		printf("%s\n", result[i++]);
	ft_free_array(result);
	return (0);
}*/