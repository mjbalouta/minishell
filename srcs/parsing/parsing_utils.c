#include "minishell.h"

void	ft_cmd_lstclear(t_command **cmd)
{
	t_command	*temp;

	while (*cmd)
	{
		free((*cmd)->comm_path);
		free_char_array((*cmd)->args);
		ft_redir_lstclear(&(*cmd)->redirection);
		temp = (*cmd)->next;
		free(*cmd);
		*cmd = temp;
	}
}

void	ft_redir_lstclear(t_redir **redir)
{
	t_redir	*temp;

	while (*redir)
	{
		free((*redir)->filename);
		temp = (*redir)->next;
		free(*redir);
		*redir = temp;
	}
}
