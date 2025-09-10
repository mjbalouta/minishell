/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:01 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/06/25 20:32:07 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_atoi.c
 * @brief converts the initial
 * portion of the string pointed to by nptr to int.
 */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		negative;
	long	num;

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

/* int	main(void)
{
	int result = ft_atoi("+1");
	printf("%d\n", result);
}
 */