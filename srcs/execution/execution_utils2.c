/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:29 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:30 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(int	*pipefd, t_shell *ms)
{
	if (pipe(pipefd) != 0)
		exit_shell(ms, 1);
}

void	close_one_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	close_both_fds(int fd1, int fd2)
{
	close_one_fd(fd1);
	close_one_fd(fd2);
}

void	free_pid(t_shell *ms)
{
	if (ms->pid)
	{
		free(ms->pid);
		ms->pid = NULL;
	}
}

void	handle_execve_error(t_cmd *command, char **envp, t_shell *ms)
{
	if (errno == EACCES || errno == EISDIR)
	{
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 126);
	}
	else if (errno == ENOENT || errno == ENOTDIR)
	{
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 127);
	}
	else
	{
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 1);
	}
}
