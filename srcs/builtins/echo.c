/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:04 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:07 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_n_option(char *arg, int *i, bool *new_line)
{
	int	j;

	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (false);
		j++;
	}
	(*i)++;
	*new_line = false;
	return (true);
}

void	builtin_echo(t_shell *ms, t_cmd *cmd)
{
	int		i;
	bool	new_line;
	bool	print_started;

	(void)ms;
	i = 1;
	new_line = true;
	print_started = false;
	while (cmd->args && cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], "-n", 2) == 0) && !print_started)
		{
			if (valid_n_option(cmd->args[i], &i, &new_line))
				continue ;
		}
		print_started = true;
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1] && cmd->args[i][0] && cmd->args[i + 1][0])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 0;
}
