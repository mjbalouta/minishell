#include "minishell.h"

/**
 * @brief Checks if token is word
 * 
 * @param temp 
 * @return int 
 */
int	verify_if_word(t_token *temp)
{
	if (temp->type == T_WORD)
		return (1);
	return (0);
}

/**
 * @brief Checks if token is pipe and if the next one is also
 * a pipe
 * 
 * @param temp 
 * @return int 
 */
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

/**
 * @brief Checks if a token is a redirect and if after there's a
 * word (filename)
 * 
 * @param temp 
 * @return int 
 */
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
 * @brief Verifies if there are empty commands, no commands or if
 * filenames are missing
 * 
 * @param ms 
 * @return -1 for error or 0 if everything is correct
 */
int	verify_tokens(t_shell *ms)
{
	t_token	*temp;
	int		is_command;

	if (!ms->token)
		return (2);
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
