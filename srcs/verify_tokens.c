#include "../includes/minishell.h"

/**
 * @brief verifies if there are empty commands or if filenames are missing
 * 
 * @param ms 
 * @return -1 for error or 0 if everything is correct
 */
int	verify_tokens(t_shell *ms)
{
	int	first_token;

	first_token = 0;
	while (ms->token)
	{
		// if ()
		if (is_redir(ms->token) == 1)
		{
			if (!ms->token->next) //se nao existir token depois de um redirect
				return (-1);
			if (ms->token->next->type != T_WORD) //se o token a seguir ao redirect nao for uma palavra
				return (-1);
		}
		if (ms->token->type == T_PIPE)
		{
			if (!ms->token->next) // se nao existir token a seguir a um pipe
				return (-1);
			if (ms->token->next->type == T_PIPE) // se o token a seguir ao pipe for outro pipe
				return (-1);
		}
		ms->token = ms->token->next;
	}
	return (0);
}
