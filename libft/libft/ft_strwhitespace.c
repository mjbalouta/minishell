/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwhitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:30:20 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 07:53:04 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strwhitespace.c
 * @brief returns a pointer to the first occurrence of a whitespace
 */

#include "libft.h"

char	*ft_strwhitespace(const char *s)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
