#include "../includes/minishell.h"

/**
 * @brief verifies if there are empty commands, no commands or if filenames are missing
 * 
 * @param ms 
 * @return -1 for error or 0 if everything is correct
 */
int	verify_tokens(t_shell *ms)
{
	int		first_token;
	t_token	*temp;
	int		is_command;

	first_token = 0;
	temp = ms->token;
	while (temp)
	{
		if (first_token == 0 && temp->type == T_PIPE) // se o primeiro token for um pipe
			return (-1);
		is_command = 0;
		while (temp && temp->type != T_PIPE)
		{
			if (temp->type == T_WORD)
				is_command = 1;
			first_token = 1;
			if (is_redir(temp) == 1)
			{
				if (!temp->next) //se nao existir token depois de um redirect
					return (-1);
				if (temp->next->type != T_WORD) //se o token a seguir ao redirect nao for uma palavra
					return (-1);
			}
			temp = temp->next;
		}
		if (is_command == 0) // o primeiro "comando" nao contem uma palavra/um comando
			return (-1);
		if (!temp)
			break ;
		if (temp->type == T_PIPE)
		{
			if (!temp->next) // se nao existir token a seguir a um pipe
				return (-1);
			if (temp->next->type == T_PIPE) // se o token a seguir ao pipe for outro pipe
				return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
