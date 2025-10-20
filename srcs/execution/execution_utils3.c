/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:32 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:33 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief defines last found redirections of different types
 * 
 * @param cmd 
 */
void	define_last_redirection(t_cmd *cmd)
{
	t_redir	*temp_redir;

	cmd->last_out_redir = NULL;
	cmd->last_append_redir = NULL;
	cmd->last_in_redir = NULL;
	temp_redir = cmd->redir;
	cmd->last_out_redir = find_last_redir(temp_redir, T_REDIRECT_OUTPUT);
	temp_redir = cmd->redir;
	cmd->last_append_redir = find_last_redir(temp_redir, T_REDIR_OUT_APPEND);
	temp_redir = cmd->redir;
	cmd->last_in_redir = find_last_redir(temp_redir, T_REDIRECT_INPUT);
}
