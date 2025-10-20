/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:51 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:52 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_shell *ms, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-", 1) == 0)
		{
			print_error("pwd: options aren't supported");
			g_exit_status = 2;
			return ;
		}
		i++;
	}
	ft_putendl_fd(ms->cwd, STDOUT_FILENO);
	g_exit_status = 0;
}
