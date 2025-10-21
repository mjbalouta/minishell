/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:56 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:57 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_shell *ms, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-", 1) == 0)
		{
			print_error("unset: options aren't supported");
			g_exit_status = 2;
			return ;
		}
		i++;
	}
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		ft_unsetenv(cmd->args[i], &ms->envp);
		if (ft_strcmp(cmd->args[i], "OLDPWD") == 0)
			ms->ignore_oldpwd = true;
		i++;
	}
	g_exit_status = 0;
}
