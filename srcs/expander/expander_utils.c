/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:44 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:45 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*delete_empty_token(t_shell *ms, t_token *to_delete, t_token *previous)
{
	t_token	*next;

	next = to_delete->next;
	if (to_delete == ms->token)
	{
		ms->token = to_delete->next;
	}
	else if (previous)
	{
		previous->next = to_delete->next;
	}
	free(to_delete->word);
	free(to_delete);
	return (next);
}

bool	is_heredoc_token(t_token *token)
{
	return (token && token->type == T_HEREDOC);
}

char	*expand_tilde(char *str, t_envp *env)
{
	char	*home;
	char	*result;

	if (str[0] != '~')
		return (str);
	home = ft_getenv("HOME", env);
	if (!home)
		return (str);
	result = ft_strjoin(home, str + 1);
	free (str);
	if (!result)
		return (NULL);
	return (result);
}

char	*expand_exit_status(char *result, int *i, t_shell *ms)
{
	char	*status_str;

	status_str = ft_itoa(g_exit_status);
	if (!status_str)
	{
		free(result);
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	}
	result = ft_strjoin_free(result, status_str);
	free(status_str);
	if (!result)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	(*i)++;
	return (result);
}

char	*expand_dollar(t_shell *ms, char *result, char *str, int *i)
{
	int		start;
	char	*varname;
	char	*value;

	if (str[*i] == '?')
		result = expand_exit_status(result, i, ms);
	else if (str[*i] == '!')
		(*i)++;
	else if (str[*i] >= '0' && str[*i] <= '9')
		(*i)++;
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		start = *i;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		varname = ft_substr(str, start, *i - start);
		value = ft_getenv(varname, ms->envp);
		if (value)
			result = ft_strjoin_free(result, value);
		free(varname);
	}
	else
		result = ft_strjoin_char(result, '$');
	return (result);
}
