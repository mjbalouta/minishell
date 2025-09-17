#include "minishell.h"

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
		|| token->type == T_REDIRECT_OUTPUT_APPEND
		|| token->type == T_HEREDOC)
		return (1);
	return (0);
}

/**
 * @brief counts args until it finds a pipe (doesn't count redirections and file names)
 * 
 * @param ms 
 * @return nr_args 
 */
int	count_args(t_shell *ms)
{
	int		nr_args;
	t_token	*temp;

	nr_args = 0;
	temp = ms->token;
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
 * @brief creates cmd list
 * 
 * @param ms 
 */
void	create_cmd_list(t_shell *ms)
{
	int			nr_args;
	int			i;
	t_command	*new_cmd_node;
	t_redir		*new_redir_node;
	t_command	*tmp;

	ms->command = ft_calloc(1, sizeof(t_command));
	if (!ms->command)
		return ;
	tmp = ms->command;
	tmp->redirection = ft_calloc(1, sizeof(t_redir));
	if (!tmp->redirection)
		return ;
	while (ms->token)
	{
		i = 0;
		nr_args = count_args(ms);
		tmp->args = ft_calloc(nr_args + 1, sizeof(char *));
		if (!tmp->args)
			return ;
		while (ms->token && ms->token->type != T_PIPE)
		{
			if (ms->token->type == T_WORD)
				tmp->args[i++] = ms->token->word;
			else if (is_redir(ms->token) == 1)
			{
				tmp->redirection->type = ms->token->type;
				ms->token = ms->token->next;
				tmp->redirection->filename = ms->token->word;
				new_redir_node = ft_calloc(1, sizeof(t_redir));
				if (!new_redir_node)
					return ;
				tmp->redirection->next = new_redir_node;
				tmp->redirection = new_redir_node;
			}
			ms->token = ms->token->next;
		}
		if (!ms->token)
			break ;
		ms->token = ms->token->next;
		new_cmd_node = ft_calloc(1, sizeof(t_command));
		if (!new_cmd_node)
			return ;
		tmp->next = new_cmd_node;
		tmp = new_cmd_node;
	}
}

