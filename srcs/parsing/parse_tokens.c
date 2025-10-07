/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:51:06 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/07 15:59:56 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*DELETE LATER*/
void	test_printing(t_shell *ms) //testing
{
	int i = 0;
	int z = 0;
	t_command *tmp = ms->command;
	while (tmp)
	{
		ft_printf("command %d:", i + 1);
		z = 0;
		while (tmp->args[z])
		{
			ft_printf("%s ", tmp->args[z]);
			z++;
		}
		if (tmp->redirection)
		{
			ft_printf("\nREDIR:\n");
			while (tmp->redirection)
			{
				ft_printf("redirection type: %d | ", tmp->redirection->type);
				ft_printf("filename: %s ", tmp->redirection->filename);
				tmp->redirection = tmp->redirection->next;
			}
		}
		i++;
		ft_printf("builtin: %d", tmp->is_builtin);
		tmp = tmp->next;
		ft_printf("\n");
	}
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
	t_redir		*last_redir;

	ms->command = ft_calloc(1, sizeof(t_command));
	if (!ms->command)
		return ;
	tmp = ms->command;
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
				new_redir_node = ft_calloc(1, sizeof(t_redir));
    			if (!new_redir_node)
        			return;
    			new_redir_node->type = ms->token->type;
    			ms->token = ms->token->next;
    			new_redir_node->filename = ms->token->word;
    			new_redir_node->next = NULL;
    			if (!tmp->redirection) //primeira iteracao
    			{
        			tmp->redirection = new_redir_node;
        			last_redir = tmp->redirection;
    			}
    			else //iteracoes seguintes
    			{
        			last_redir->next = new_redir_node;
        			last_redir = last_redir->next;
    			}
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
		tmp = tmp->next;
	}
	verify_if_bultin(ms);
	// test_printing(ms); //function for testing
}

