#include "minishell.h"

char	*expand_tilde(char *str, t_envp *env)
{
	char	*home;

	if (str[0] != '~')
		return (ft_strdup(str));
	home = ft_getenv("HOME", env);
	if (!home)
		return (ft_strdup(str));
	return (ft_strjoin(home, str + 1));
}

char	*expand_exit_status(char *result, int *i, t_shell *ms)
{
	char	*status_str;

	status_str = ft_itoa(ms->exit_status);
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

char	*expand_variables(char *str, t_shell *ms)
{
	int		i;
	int		start;
	int		in_single;
	int		in_double;
	char	*result;
	char	*value;
	char	*varname;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	value = NULL;
	varname = NULL;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (str[i] == '$' && !in_single)
		{
			i++;
			if (str[i] == '?')
				result = expand_exit_status(result, &i, ms);
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				start = i;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				varname = ft_substr(str, start, i - start);
				value = ft_getenv2(varname, ms->envp);
				result = ft_strjoin_free(result, value);
				free(varname);
			}
			else
				result = ft_strjoin_char(result, '$');
		}
		else
			result = ft_strjoin_char(result, str[i++]);
	}
	return (result);
}

char	*expand_word(char *word, t_shell *ms)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(word);
	if (!result)
		return (NULL);
	if (result[0] == '~')
		result = expand_tilde(result, ms->envp);
	if (!result)
		return (NULL);
	tmp = expand_variables(result, ms);
	free(result);
	result = tmp;
	return (result);
}

void	expander(t_shell *ms)
{
	t_token	*current;
	char	*expanded_word;

	// ft_printf("--- Expander Start ---\n");
	// ft_token_lstprint(ms->token); // Debug: print tokens before expansion
	current = ms->token;
	while (current != NULL)
	{
		if (current->type == T_WORD)
		{
			expanded_word = expand_word(current->word, ms);
			if (expanded_word == NULL)
				print_error_and_exit(ms, "Expansion error", EXIT_FAILURE);
			free(current->word);
			current->word = expanded_word;
		}
		current = current->next;
	}
	// ft_printf("--- Expander End ---\n");
	// ft_token_lstprint(ms->token); // Debug: print tokens after expansion
}
