/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:51:06 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/08 17:05:25 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*DELETE LATER*/
// void	test_printing(t_shell *ms) //testing
// {
// 	int i = 0;
// 	int z = 0;
// 	t_command *tmp = ms->command;
// 	while (tmp)
// 	{
// 		ft_printf("command %d:", i + 1);
// 		z = 0;
// 		while (tmp->args[z])
// 		{
// 			ft_printf("%s ", tmp->args[z]);
// 			z++;
// 		}
// 		if (tmp->redir)
// 		{
// 			ft_printf("\nREDIR:\n");
// 			while (tmp->redir)
// 			{
// 				ft_printf("redir type: %d | ", tmp->redir->type);
// 				ft_printf("filename: %s ", tmp->redir->filename);
// 				tmp->redir = tmp->redir->next;
// 			}
// 		}
// 		i++;
// 		ft_printf("builtin: %d", tmp->is_builtin);
// 		tmp = tmp->next;
// 		ft_printf("\n");
// 	}
// }

void	create_redir_node(t_shell *ms, t_command *command)
{
	t_redir		*new_redir_node;
	t_redir		*last_redir;
	
	new_redir_node = ft_calloc(1, sizeof(t_redir));
    if (!new_redir_node)
    	return;
    new_redir_node->type = ms->token->type;
    ms->token = ms->token->next;
    new_redir_node->filename = ms->token->word;
    new_redir_node->next = NULL;
    if (!command->redir) //primeira iteracao
   		command->redir = new_redir_node;
    else //iteracoes seguintes
    {
    	last_redir = command->redir;
        while (last_redir->next)
            last_redir = last_redir->next;
        last_redir->next = new_redir_node;
    }
}
//ACRESCENTAR UM POINTER PARA PERCORRER A LISTA DE TOKENS (PARA NAO PERCORRER A LISTA)
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

	ms->command = ft_calloc(1, sizeof(t_command));
	if (!ms->command)
		return ;
	cmd_temp = ms->command;
	while (ms->token)
	{
		i = 0;
		cmd_temp->args = ft_calloc(count_args(ms) + 1, sizeof(char *));
		if (!cmd_temp->args)
			return ;
		while (ms->token && ms->token->type != T_PIPE)
		{
			if (ms->token->type == T_WORD)
				cmd_temp->args[i++] = ms->token->word;
			else if (is_redir(ms->token) == 1)
				create_redir_node(ms, cmd_temp);
			ms->token = ms->token->next;
		}
		if (!ms->token)
			break ;
		ms->token = ms->token->next;
		new_cmd_node = ft_calloc(1, sizeof(t_command));
		if (!new_cmd_node)
			return ;
		cmd_temp->next = new_cmd_node;
		cmd_temp = cmd_temp->next;
	}
	// test_printing(ms); //function for testing
}

