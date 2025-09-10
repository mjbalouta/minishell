/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:23:34 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:29:51 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putnbr_fd.c
 * @brief Outputs the integer ’n’ to the specified file
descriptor.
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	array[10];
	int		i;

	num = n;
	i = 0;
	if (num == 0)
		write (fd, "0", 1);
	if (num < 0)
	{
		num = -num;
		write(fd, "-", 1);
	}
	while (num > 0)
	{
		array[i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	i = i - 1;
	while (i >= 0)
		write(fd, &array[i--], 1);
}

/*int main(void)
{
    ft_putnbr_fd(9, 1);
    //printf("\n%d\n", INT_MIN);
    return (0);
}*/