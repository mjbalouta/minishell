/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:27 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:10:28 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_token(char *word, t_token_type type, t_token **head,
		char **input)
{
	t_token	*token;

	token = ft_token_lstnew(word, type);
	if (!token)
	{
		ft_token_lstclear(head);
		return (EXIT_FAILURE);
	}
	ft_token_lstadd_back(head, token);
	if (type == T_HEREDOC || type == T_REDIR_OUT_APPEND)
		(*input)++;
	return (EXIT_SUCCESS);
}

static int	process_token_redir_pipe(t_token **head, char **input, int ret)
{
	if (**input == '<')
	{
		if (*(*input + 1) == '<')
			ret = add_token("<<", T_HEREDOC, head, input);
		else
			ret = add_token("<", T_REDIRECT_INPUT, head, input);
	}
	else
	{
		if (**input == '>')
		{
			if (*(*input + 1) == '>')
				ret = add_token(">>", T_REDIR_OUT_APPEND, head, input);
			else
				ret = add_token(">", T_REDIRECT_OUTPUT, head, input);
		}
		else
			if (**input == '|')
				ret = add_token("|", T_PIPE, head, input);
	}
	(*input)++;
	return (ret);
}

static int	process_token_word(t_token **head, char **input)
{
	char	*word;
	size_t	i;
	int		ret;

	i = 0;
	while ((*input)[i] && !ft_isseparator((*input)[i]))
	{
		if (ft_isquote((*input)[i]))
		{
			if (!find_matching_quote((*input)[i], *input, &i))
				return (print_error("Syntax error: unmatched quote"),
					EXIT_FAILURE);
		}
		else
			i++;
	}
	word = ft_substr(*input, 0, i);
	if (!word)
		return (EXIT_FAILURE);
	ret = add_token(word, T_WORD, head, input);
	free(word);
	if (ret != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	*input += i;
	return (EXIT_SUCCESS);
}

int	tokenizer(t_shell *ms)
{
	t_token	*head;
	char	*input;

	head = NULL;
	input = ms->input;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '<' || *input == '>' || *input == '|')
		{
			if (process_token_redir_pipe(&head, &input, 0) != EXIT_SUCCESS)
				return (ft_token_lstclear(&head), -1);
		}
		else
			if (process_token_word(&head, &input) != EXIT_SUCCESS)
				return (ft_token_lstclear(&head), -1);
	}
	free(ms->input);
	ms->input = NULL;
	ms->token = head;
	return (EXIT_SUCCESS);
}
