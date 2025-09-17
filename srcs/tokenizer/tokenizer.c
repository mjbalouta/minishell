#include "minishell.h"

static void	add_token(char *word, t_token_type type, t_shell ms)
{
	(void)ms;
	printf("Add token word: %s type %d\n");
}

static void	add_token_redir_pipe(t_token *head, char *input)
{
	if (*input == '<')
		if (*(input + 1) == '<')
		{
			add_token('<<', T_HEREDOC, &head);
			input++;
		}
		else
			add_token('<', T_REDIRECT_INPUT, &head);
	else
		if (*input == '>')
			if (*(input + 1) == '>')
			{
				add_token('>>', T_REDIRECT_OUTPUT_APPEND, &head);
				input++;
			}
			else
				add_token('>', T_REDIRECT_OUTPUT, &head);
	else
		if (*input == '|')
			add_token('|', T_PIPE, &head);
	input++;
}

static void	add_token_word(t_token *head, char *input)
{
	printf("Treat word\n");
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
		if(*input == '<' || *input == '>' || *input == '|')
			add_token_redir_pipe(&head, &input);
		else
			add_token_word(&head, &input);
	}
	free(ms->input);
	ms->input = NULL;
	return (head);
}
