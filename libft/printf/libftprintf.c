/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:56:23 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/19 11:56:23 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static	int	ft_check_format(va_list args, int count, const char *format, int i)
{
	if (format[i] == 'c')
		count = ft_printchar(va_arg(args, int), count);
	else if (format[i] == 's')
		count = ft_printstring(va_arg(args, char *), count);
	else if (format[i] == 'p')
		count = ft_printaddress(va_arg(args, void *), count);
	else if (format[i] == 'd' || format[i] == 'i')
		count = ft_printdecimal(va_arg(args, int), count);
	else if (format[i] == 'u')
		count = ft_printunsigned(va_arg(args, unsigned int), count);
	else if (format[i] == 'x')
		count = ft_printhexa(va_arg(args, unsigned int), count, 1);
	else if (format[i] == 'X')
		count = ft_printhexa(va_arg(args, unsigned int), count, 0);
	else if (format[i] == '%')
	{
		count++;
		write (1, "%", 1);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count_letters;

	va_start(args, format);
	i = 0;
	count_letters = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count_letters = ft_check_format(args, count_letters, format, i);
		}
		else
		{
			write(1, &format[i], 1);
			count_letters++;
		}
		i++;
	}
	va_end(args);
	return (count_letters);
}

//int main(void)
//{
//	char string[] = "maria joao";
// 	char c = 'c';
//  int	a = INT_MIN;
// 	int b = INT_MIN;
// 	int e = -10;
// 	int f = 5;
// 	unsigned int d = 0;
//int	result;
//int original;
// 	char str[] = "a %%maria";
// 	int *ptr = &f;
// 	printf("%%s TEST:\n");
// 	result = ft_printf("c: a %s estuda\n", string);
// 	original = printf("o: a %s estuda\n", string);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
// 	printf("\n%%c TEST:\n");
// 	result = ft_printf("c: %c e %i\n", c, b);
// 	original = printf("o: %c e %i\n", c, b);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
	//printf("\n%%d TEST:\n");
	//result = ft_printf("c: %d\n", -1);
	//original = printf("o: %d\n", -1);
	//printf("printed %d characters.\n", result);
//printf("printed %d characters.\n", original);
// 	printf("\n%%i TEST:\n");
// 	result = ft_printf("c: %i\n", b);
// 	original = printf("o: %i\n", b);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
/* printf("\n%%u TEST:\n");
 	result = ft_printf("c: %u\n", 0);
 	original = printf("o: %u\n", 0);
 	printf("printed %d characters.\n", result);
 	printf("printed %d characters.\n", original);
 	result = ft_printf("c: %u\n", -1);
 	original = printf("o: %u\n", -1); */
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
// 	printf("\n%%X AND %%x TEST:\n");
// 	result = ft_printf("c: %x\n", e);
// 	original = printf("o: %x\n", e);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
// 	result = ft_printf("c: %X\n", e);
// 	original = printf("o: %X\n", e);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
// 	printf("\n%% TEST:\n");
// 	result = ft_printf("c: %s\n", str);
// 	original = printf("o: %s\n", str);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
// 	printf("\n%%p TEST:\n");
// 	result = ft_printf("c: %p\n", ptr);
// 	original = printf("o: %p\n", ptr);
// 	printf("printed %d characters.\n", result);
// 	printf("printed %d characters.\n", original);
//}
