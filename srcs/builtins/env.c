/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:11 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *ms, t_cmd *cmd)
{
	char	**array;

	if (cmd->args && cmd->args[1])
	{
		print_error("env: options or arguments aren't supported");
		g_exit_status = 1;
		return ;
	}
	array = ft_envp_lst_to_char_array(ms, false);
	print_array_of_char(array);
	free_char_array(array);
	g_exit_status = 0;
}
