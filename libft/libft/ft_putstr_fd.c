/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:22:15 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/15 12:42:33 by josemigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putstr_fd.c
 * @brief Outputs the string ’s’ to the specified file
descriptor.
 */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd != -1)
		write(fd, s, ft_strlen(s));
}

/*int main(void)
{
    char s[] = "maria";
    ft_putstr_fd(s, 1);
    return (0);
}*/