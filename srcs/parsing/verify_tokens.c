#include "minishell.h"

int	verify_if_word(t_token *temp)
{
	if (temp->type == T_WORD)
		return (1);
	return (0);
}

int	verify_pipe(t_token *temp)
{
	if (temp->type == T_PIPE)
	{
		if (!temp->next)
			return (-1);
		if (temp->next->type == T_PIPE)
			return (-1);
	}
	return (0);
}

int	verify_redirect(t_token *temp)
{
	if (is_redir(temp) == 1)
	{
		if (!temp->next)
			return (-1);
		if (temp->next->type != T_WORD)
			return (-1);
	}
	return (0);
}

/**
 * @brief verifies if there are empty commands, no commands or if
 * filenames are missing
 * 
 * @param ms 
 * @return -1 for error or 0 if everything is correct
 */
int	verify_tokens(t_shell *ms)
{
	t_token	*temp;
	int		is_command;

	temp = ms->token;
	if (temp && temp->type == T_PIPE)
		return (-1);
	while (temp)
	{
		is_command = 0;
		while (temp && temp->type != T_PIPE)
		{
			is_command = verify_if_word(temp);
			if (verify_redirect(temp) == -1)
				return (-1);
			temp = temp->next;
		}
		if (is_command == 0)
			return (-1);
		if (!temp)
			break ;
		if (verify_pipe(temp) == -1)
			return (-1);
		temp = temp->next;
	}
	return (0);
}
