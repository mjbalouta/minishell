/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:08 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:10:09 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		print_error("Not prepared to handle arguments");
		exit(EXIT_FAILURE);
	}
}

void	print_error_and_exit(t_shell *ms, char *message, int exit_status)
{
	print_error(message);
	exit_shell(ms, exit_status);
}

void	print_error(char *message)
{
	ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	reset_fds(t_shell *ms)
{
	dup2(ms->in_fd, STDIN_FILENO);
	dup2(ms->out_fd, STDOUT_FILENO);
	close_both_fds(ms->in_fd, ms->out_fd);
}
