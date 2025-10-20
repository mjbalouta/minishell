/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:07:53 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:07:54 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_shell *ms, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		builtin_export(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_unset(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(ms, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(ms, cmd);
}
