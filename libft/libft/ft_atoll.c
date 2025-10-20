/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:01 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/17 22:37:55 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_atoll.c
 * @brief converts the initial
 * portion of the string pointed to by nptr to long long.
 */

#include "libft.h"

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			negative;
	long long	num;

	i = 0;
	num = 0;
	negative = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10;
		num = num + (nptr[i] - '0');
		i++;
	}
	if (negative == 1)
		return (-num);
	return (num);
}
