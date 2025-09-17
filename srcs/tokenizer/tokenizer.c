#include "minishell.h"

static bool	add_token(char *word, t_token_type type, t_token **head)
{
	t_token	*token;

	token = ft_token_lstnew(word, type);
	if (!token)
	{
		ft_token_lstclear(head);
		return (false);
	}
	ft_token_lstadd_back(head, token);
	return (true);

}

static bool	process_token_redir_pipe(t_token **head, char **input)
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
	return (true);
}

static bool	process_token_word(t_token **head, char **input)
{
	char	*word;
	size_t	i;

	i = 0;
	while ((*input)[i] && !ft_isseparator((*input)[i]))
	{
		if (ft_isquote((*input)[i]))
		{
			// Quotes handling
			if (!find_matching_quote((*input)[i], *input, &i))
				return(printf("Matching quote not found!!!"), false);
		}
		else
			i++;
	}
	word = ft_substr(*input, 0, i);
	if (!word)
		return (NULL);
	add_token(word, T_WORD, head);
	*input += i;
	return (true);
}

t_token *tokenizer(t_shell *ms)
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
			break;
		if(*input == '<' || *input == '>' || *input == '|')
			process_token_redir_pipe(&head, &input);
		else
			process_token_word(&head, &input);
	}
	free(ms->input);
	ms->input = NULL;
	return (head);
}
