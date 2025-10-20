/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:12 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:10:13 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signal(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_exit_status = 130;
		}
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: (core dumped)\n", 1);
			g_exit_status = 131;
		}
		else
			g_exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
}
