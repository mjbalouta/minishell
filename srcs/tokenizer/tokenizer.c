#include "minishell.h"

static void	add_token(char *word, t_token_type type, t_token **head)
{
	t_token	*token;

	token = ft_token_lstnew(word, type);
	if (!token)
	{
		ft_token_lstclear(head);
		return ;
	}
	ft_token_lstadd_back(head, token);
	return ;
}

int	process_token_redir_pipe(t_token **head, char **input)
{
	if (**input == '<')
		if (*(*input + 1) == '<')
		{
			add_token("<<", T_HEREDOC, head);
			(*input)++;
		}
	else
		add_token("<", T_REDIRECT_INPUT, head);
	else
		if (**input == '>')
			if (*(*input + 1) == '>')
			{
				add_token(">>", T_REDIRECT_OUTPUT_APPEND, head);
				(*input)++;
			}
	else
		add_token(">", T_REDIRECT_OUTPUT, head);
	else
		if (**input == '|')
			add_token("|", T_PIPE, head);
	(*input)++;
	return (0);
}

int	process_token_word(t_token **head, char **input)
{
	char	*word;
	size_t	i;

	i = 0;
	while ((*input)[i] && !ft_isseparator((*input)[i]))
	{
		if (ft_isquote((*input)[i]))
		{
			if (!find_matching_quote((*input)[i], *input, &i))
			{
				*input += i;
				print_error("Syntax error: unmatched quote");
				return (-1);
			}
		}
		else
			i++;
	}
	word = ft_substr(*input, 0, i);
	if (!word)
		return (-1);
	add_token(word, T_WORD, head);
	free(word);
	*input += i;
	return (0);
}

int	tokenizer(t_shell *ms)
{
	t_token	*head;
	char	*input;

	head = NULL;
	input = ms->input;
	ft_token_lstclear(&ms->token);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '<' || *input == '>' || *input == '|')
		{
			if (process_token_redir_pipe(&head, &input) != 0)
				return (ft_token_lstclear(&head), -1);
		}
		else
			if (process_token_word(&head, &input) != 0)
				return (ft_token_lstclear(&head), -1);
	}
	free(ms->input);
	ms->input = NULL;
	ms->token = head;
	return (0);
}
