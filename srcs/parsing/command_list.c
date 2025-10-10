/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:51:06 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/10 15:29:40 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*DELETE LATER*/
void	test_printing(t_shell *ms) //testing
{
	int i = 0;
	int z = 0;
	t_command *tmp = ms->command;
	while (tmp)
	{
		ft_printf("COMMAND %d:", i + 1);
		z = 0;
		while (tmp->args[z])
		{
			ft_printf("%s ", tmp->args[z]);
			z++;
		}
		if (tmp->redir)
		{
			ft_printf("\nREDIR:\n");
			while (tmp->redir)
			{
				ft_printf("redir type: %d | ", tmp->redir->type);
				ft_printf("filename: %s ", tmp->redir->filename);
				tmp->redir = tmp->redir->next;
			}
		}
		i++;
		ft_printf("\nis builtin? %d", tmp->is_builtin);
		tmp = tmp->next;
		ft_printf("\n");
	}
}

void	create_redir_node(t_token **token, t_command *command)
{
    t_redir		*new_redir_node;
    t_redir		*last_redir;
    
    new_redir_node = ft_calloc(1, sizeof(t_redir));
    if (!new_redir_node)
        return;
    new_redir_node->type = (*token)->type;
    *token = (*token)->next;
    new_redir_node->filename = (*token)->word;
    new_redir_node->next = NULL;
    if (!command->redir)
        command->redir = new_redir_node;
    else
    {
        last_redir = command->redir;
        while (last_redir->next)
            last_redir = last_redir->next;
        last_redir->next = new_redir_node;
    }
}

/**
 * @brief creates cmd list
 * 
 * @param ms 
 */
void	create_cmd_list(t_shell *ms)
{
	int			i;
	t_command	*new_cmd_node;
	t_command	*cmd_temp;
	t_token		*token_temp;

	ms->command = ft_calloc(1, sizeof(t_command));
	if (!ms->command)
		return ;
	cmd_temp = ms->command;
	token_temp = ms->token;
	while (token_temp)
	{
		i = 0;
		cmd_temp->args = ft_calloc(count_args(token_temp) + 1, sizeof(char *));
		if (!cmd_temp->args)
			return ;
		while (token_temp && token_temp->type != T_PIPE)
		{
			if (token_temp->type == T_WORD)
				cmd_temp->args[i++] = token_temp->word;
			else if (is_redir(token_temp) == 1)
				create_redir_node(&token_temp, cmd_temp);
			token_temp = token_temp->next;
		}
		if (!token_temp)
			break ;
		token_temp = token_temp->next;
		new_cmd_node = ft_calloc(1, sizeof(t_command));
		if (!new_cmd_node)
			return ;
		cmd_temp->next = new_cmd_node;
		cmd_temp = cmd_temp->next;
	}
	// test_printing(ms); //function for testing
}

