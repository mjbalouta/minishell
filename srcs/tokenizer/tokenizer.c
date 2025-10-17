#include "minishell.h"

static int	add_token(char *word, t_token_type type, t_token **head)
{
	t_token	*token;

	token = ft_token_lstnew(word, type);
	if (!token)
	{
		ft_token_lstclear(head);
		return (EXIT_FAILURE);
	}
	ft_token_lstadd_back(head, token);
	return (EXIT_SUCCESS);
}

int	process_token_redir_pipe(t_token **head, char **input)
{
	int		ret;

	ret = 0;
	if (**input == '<')
		if (*(*input + 1) == '<')
		{
			ret = add_token("<<", T_HEREDOC, head);
			(*input)++;
		}
	else
		ret = add_token("<", T_REDIRECT_INPUT, head);
	else
		if (**input == '>')
			if (*(*input + 1) == '>')
			{
				ret = add_token(">>", T_REDIR_OUT_APPEND, head);
				(*input)++;
			}
	else
		ret = add_token(">", T_REDIRECT_OUTPUT, head);
	else
		if (**input == '|')
			ret = add_token("|", T_PIPE, head);
	(*input)++;
	return (ret);
}

int	process_token_word(t_token **head, char **input)
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
			{
				*input += i;
				print_error("Syntax error: unmatched quote");
				return (EXIT_FAILURE);
			}
		}
		else
			i++;
	}
	word = ft_substr(*input, 0, i);
	if (!word)
		return (EXIT_FAILURE);
	ret = add_token(word, T_WORD, head);
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
			if (process_token_redir_pipe(&head, &input) != EXIT_SUCCESS)
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
