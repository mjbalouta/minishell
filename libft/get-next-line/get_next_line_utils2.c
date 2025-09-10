/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:37:11 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/28 16:57:23 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init_remain(char **remain)
{
	if (!*remain)
		*remain = ft_ncalloc(BUFFER_SIZE + 1, sizeof(char));
	return (*remain != NULL);
}

char	*free_remain(char **remain)
{
	free(*remain);
	*remain = NULL;
	return (NULL);
}

void	initialize_memo(int *found, char **result)
{
	*found = 2;
	*result = NULL;
}
