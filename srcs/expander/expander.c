#include "minishell.h"

char *expand_tilde(char *str, t_envp *env)
{
    char *home;

    if (str[0] != '~')
        return (ft_strdup(str));
    home = ft_getenv("HOME", env);
    return (ft_strjoin(home, str + 1));
}

char	*expand_word(char *word, t_shell *ms)
{
	char	*result;

	result = ft_strdup(word);
	if (!result)
		return (NULL);
	if (result[0] == '~')
		result = expand_tilde(result, ms->envp);
	if (!result)
		return (NULL);
	return (result);
}

void	expander(t_shell *ms)
{
	t_token	*current;
	char	*expanded_word;

	ft_printf("--- Expander Start ---\n");
	ft_token_lstprint(ms->token); // Debug: print tokens before expansion
	current = ms->token;
	while (current != NULL)
	{
		if (current->type == T_WORD)
		{
			expanded_word = expand_word(current->word, ms);
			if (expanded_word == NULL)
				print_error_and_exit(ms, "Expansion error\n", EXIT_FAILURE);
			free(current->word);
			current->word = expanded_word;
		}
		current = current->next;
	}
	ft_printf("--- Expander End ---\n");
	ft_token_lstprint(ms->token); // Debug: print tokens after expansion
}
