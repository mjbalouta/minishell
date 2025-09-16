#include "../includes/minishell.h"

/**
 * @brief counts args until it finds a pipe
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
		if (!(temp->type == T_REDIRECT_INPUT
			|| temp->type == T_REDIRECT_OUTPUT
			|| temp->type == T_REDIRECT_OUTPUT_APPEND
			|| temp->type == T_HEREDOC)) //estou a contar filenames como args e nao posso
			nr_args++;
		temp = temp->next;
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
	t_command	*new_node;

	ms->command = ft_calloc(1, sizeof(t_command));
	if (!ms->command)
		return ;
	while (ms->token)
	{
		i = 0;
		nr_args = count_args(ms);
		ms->command->args = ft_calloc(nr_args + 1, sizeof(char *));
		if (!ms->command->args)
			return ;
		while (ms->token && ms->token->type != T_PIPE)
		{
			if (ms->token->type == T_WORD)
				ms->command->args[i++] = ms->token->word;
			else if (ms->token->type == T_REDIRECT_INPUT
					|| ms->token->type == T_REDIRECT_OUTPUT
					|| ms->token->type == T_REDIRECT_OUTPUT_APPEND
					|| ms->token->type == T_HEREDOC)
			{
				ms->command->redirection->type = ms->token->type;
				ms->token = ms->token->next;
				ms->command->redirection->filename = ms->token->word;
				ms->command->redirection = ms->command->redirection->next;
			}
			ms->token = ms->token->next;
		}
		ms->token = ms->token->next;
		new_node = ft_calloc(1, sizeof(t_command));
		if (!new_node)
			return ;
		ms->command->next = new_node;
		ms->command = new_node;
	}
}

