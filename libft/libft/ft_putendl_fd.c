/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:22:41 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/15 12:43:53 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putendl_fd.c
 * @brief Outputs the string ’s’ to the specified file
descriptor followed by a newline.
 */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (fd != -1)
	{
		write(fd, s, ft_strlen(s));
		ft_putchar_fd('\n', fd);
	}
}

/*int main(void)
{
    char s[] = "maria";
    ft_putendl_fd(s, 1);
    return (0);
}*/