#include "minishell.h"

char	*expand_tilde(char *str, t_envp *env);
char	*expand_exit_status(char *result, int *i, t_shell *ms);
char	*expand_dollar(t_shell *ms, char *result, char *str, int *i);

static int	handle_quotes(t_token *token, int *in_single, int *in_double,
		char c)
{
	if (c == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		token->quoted = true;
		return (1);
	}
	else if (c == '"' && !*in_single)
	{
		*in_double = !*in_double;
		token->quoted = true;
		return (1);
	}
	return (0);
}

char	*expand_variables(t_token *token, char *str, t_shell *ms)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*result;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (handle_quotes(token, &in_single, &in_double, str[i]))
			i++;
		else if (str[i] == '$' && !in_single)
		{
			i++;
			result = expand_dollar(ms, result, str, &i);
		}
		else
			result = ft_strjoin_char(result, str[i++]);
	}
	free(str);
	return (result);
}

void	expand_word(t_token *current, t_shell *ms)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(current->word);
	if (!result)
		print_error_and_exit(ms, "Expansion error", EXIT_FAILURE);
	if (result[0] == '~')
		if ((result[1] == '/') || (result[1] == '\0'))
			result = expand_tilde(result, ms->envp);
	if (!result)
		print_error_and_exit(ms, "Expansion error", EXIT_FAILURE);
	tmp = expand_variables(current, result, ms);
	if (!tmp)
		print_error_and_exit(ms, "Expansion error", EXIT_FAILURE);
	if (!current->quoted && ((ft_strchr(tmp, ' ')) || (ft_strchr(tmp, '\t'))))
		insert_expanded_tokens(ms, current, tmp);
	else
	{
		free(current->word);
		current->word = tmp;
	}
}

void	expander(t_shell *ms)
{
	t_token	*current;
	t_token	*previous;

	current = ms->token;
	previous = NULL;
	while (current != NULL)
	{
		if (current->type == T_WORD && !is_heredoc_token(previous))
		{
			expand_word(current, ms);
			if ((current->word[0] == '\0') && !current->quoted)
			{
				current = delete_empty_token(ms, current, previous);
				continue ;
			}
		}
		previous = current;
		current = current->next;
	}
}
