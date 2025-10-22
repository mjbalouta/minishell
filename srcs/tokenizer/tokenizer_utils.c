/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/22 11:39:25 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isquote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	ft_isseparator(int c)
{
	if (ft_isspace(c) || c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

bool	find_matching_quote(char quote, char *input, size_t *i)
{
	(*i)++;
	g_exit_status = 2;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == '\0')
		return (false);
	(*i)++;
	g_exit_status = 0;
	return (true);
}
