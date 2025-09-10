/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:49:56 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/06/21 15:14:20 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_itoa.c
 * @brief Allocates memory (using malloc(3)) and returns
a string representing the integer received as an
argument. Negative numbers must be handled.
 */

#include "libft.h"

static char	*ft_putnbr(long num, char *str, int nr_digits, int is_negative)
{
	if (is_negative)
	{
		str[0] = '-';
	}
	str[is_negative + nr_digits] = '\0';
	while (num > 0 && nr_digits > 0)
	{
		str[is_negative + nr_digits - 1] = (num % 10) + '0';
		num = num / 10;
		nr_digits--;
	}
	return (str);
}

static int	ft_count_digits(long num)
{
	int	nr_digits;

	nr_digits = 0;
	while (num > 0)
	{
		num = num / 10;
		nr_digits++;
	}
	return (nr_digits);
}

char	*ft_memory_alloc(int is_negative, int nr_digits)
{
	char	*str;

	if (is_negative == 1)
		str = (char *)ft_calloc((nr_digits + 2), sizeof(char));
	else
		str = (char *)ft_calloc((nr_digits + 1), sizeof(char));
	return (str);
}

char	*ft_itoa(int n)
{
	int		nr_digits;
	char	*str;
	int		is_negative;
	long	num;

	num = n;
	is_negative = 0;
	if (num == 0)
		return (ft_strdup("0"));
	if (num < 0)
	{
		is_negative = 1;
		num = num * (-1);
	}
	nr_digits = ft_count_digits(num);
	str = ft_memory_alloc(is_negative, nr_digits);
	if (!str)
		return (NULL);
	str = ft_putnbr(num, str, nr_digits, is_negative);
	return (str);
}

// int	main(void)
// {
// 	int num = -9874;
// 	char *res;
// 	res = ft_itoa(num);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }