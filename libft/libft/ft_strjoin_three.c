/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 23:58:48 by josemigu          #+#    #+#             */
/*   Updated: 2025/10/18 23:58:49 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = ft_strjoin(s1, s2);
	if (!ptr1)
		return (NULL);
	ptr2 = ft_strjoin(ptr1, s3);
	free(ptr1);
	if (!ptr2)
		return (NULL);
	return (ptr2);
}
