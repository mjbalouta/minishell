#include "minishell.h"

/**
 * @brief counts args until it finds a pipe (doesn't count redirections
 * and file names)
 * 
 * @param ms 
 * @return nr_args 
 */
int	count_args(t_token *token)
{
	int		nr_args;
	t_token	*temp;

	nr_args = 0;
	temp = token;
	while (temp && temp->type != T_PIPE)
	{
		if (is_redir(temp) == 1)
			temp = temp->next->next;
		else
		{
			nr_args++;
			temp = temp->next;
		}
	}
	return (nr_args);
}

/**
 * @brief checks if token->type is redirection or heredoc
 * 
 * @param token 
 * @return 1 = redirection; 0 != redirection 
 */
int	is_redir(t_token *token)
{
	if (token->type == T_REDIRECT_INPUT
		|| token->type == T_REDIRECT_OUTPUT
		|| token->type == T_REDIR_OUT_APPEND
		|| token->type == T_HEREDOC)
		return (1);
	return (0);
}

void	ft_cmd_lstclear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->args)
			free(current->args);
		if (current->comm_path)
			free(current->comm_path);
		if (current->redir)
			free_redirection_list(current->redir);
		if (current->heredoc_fd != -1)
		{
			close(current->heredoc_fd);
			current->heredoc_fd = -1;
		}
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	free_redirection_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
