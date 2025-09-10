/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:56:14 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/19 11:56:14 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

int		ft_printf(const char *format, ...);

int		ft_printstring(char *string, int count_letters);

int		ft_printchar(int c, int count_letters);

int		ft_printdecimal(int num, int count_letters);

int		ft_printunsigned(unsigned int a, int count_letters);

int		ft_printhexa(unsigned int num, int count_letters, int lowcase);

int		ft_printaddress(void *p, int count_letters);

char	*ft_uitoa(unsigned int num, int size);
