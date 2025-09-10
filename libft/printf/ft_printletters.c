/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printletters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:30 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/19 22:58:30 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printstring(char *str, int count_letters)
{
	int	i;

	i = 0;
	if (!str)
	{
		write (1, "(null)", 6);
		return (count_letters + 6);
	}
	while (str[i])
	{
		write (1, &str[i], 1);
		count_letters++;
		i++;
	}
	return (count_letters);
}

int	ft_printchar(int c, int count_letters)
{
	write(1, &c, 1);
	return (count_letters + 1);
}
