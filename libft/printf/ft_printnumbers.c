/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnumbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:22 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/19 22:58:22 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printdecimal(int num, int count_letters)
{
	char	*ptr;
	int		i;

	ptr = ft_itoa(num);
	i = 0;
	while (ptr[i])
	{
		write (1, &ptr[i], 1);
		i++;
	}
	free(ptr);
	count_letters += i;
	return (count_letters);
}

char	*ft_uitoa(unsigned int num, int size)
{
	char	*ptr;

	ptr = ft_calloc(size + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if (num == 0)
		ptr[0] = '0';
	ptr[size] = '\0';
	while (num > 0)
	{
		ptr[size - 1] = (num % 10) + '0';
		size--;
		num = num / 10;
	}
	return (ptr);
}

int	ft_printunsigned(unsigned int a, int count_letters)
{
	char			*ptr;
	int				count;
	unsigned int	num;
	int				i;

	count = 0;
	num = a;
	i = 0;
	if (num == 0)
		return (count_letters += write (1, "0", 1));
	else
	{
		while (num > 0)
		{
			num /= 10;
			count++;
		}
	}
	ptr = ft_uitoa(a, count);
	if (!ptr)
		return (count_letters);
	while (i < count)
		count_letters += write (1, &ptr[i++], 1);
	free(ptr);
	return (count_letters);
}

int	ft_printhexa(unsigned int num, int count_letters, int lowcase)
{
	char	*base;
	char	array[16];
	int		i;

	base = "0123456789ABCDEF";
	i = 0;
	if (num == 0)
	{
		write (1, "0", 1);
		return (count_letters + 1);
	}
	while (num > 0)
	{
		if (lowcase == 1 && (num % 16) >= 10)
			array[i] = base[num % 16] + 32;
		else
			array[i] = base[num % 16];
		i++;
		count_letters++;
		num = num / 16;
	}
	while (--i >= 0)
		write (1, &array[i], 1);
	return (count_letters);
}

int	ft_printaddress(void *p, int count_letters)
{
	unsigned long	num;
	char			*base;
	char			array[16];
	int				i;

	if (p == NULL)
	{
		write(1, "(nil)", 5);
		return (count_letters + 5);
	}
	num = (unsigned long)p;
	i = 0;
	write (1, "0x", 2);
	count_letters += 2;
	base = "0123456789abcdef";
	while (num > 0)
	{
		array[i++] = base[num % 16];
		num = num / 16;
	}
	while (--i >= 0)
		count_letters += write (1, &array[i], 1);
	return (count_letters);
}
