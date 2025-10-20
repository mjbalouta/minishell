/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:14 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:15 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespaces(char **str)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
}

int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
		if (**str < '0' || **str > '9')
			return (0);
	}
	return (sign);
}
