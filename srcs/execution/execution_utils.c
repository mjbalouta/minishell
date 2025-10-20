/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:26 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 17:16:39 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pids_container(t_shell *ms)
{
	int	nr_cmds;

	nr_cmds = count_commands(ms);
	ms->pid = malloc(sizeof(pid_t) * nr_cmds);
	if (!ms->pid)
		return ;
}

/**
 * @brief counts commands (divided by pipes)
 * 
 * @param ms 
 * @return nr_commands
 */
int	count_commands(t_shell *ms)
{
	t_cmd	*temp;
	int		nr_commands;

	temp = ms->command;
	nr_commands = 0;
	while (temp)
	{
		nr_commands++;
		temp = temp->next;
	}
	return (nr_commands);
}

/**
 * @brief waits for every process id (pid) to end
 * 
 * @param ms 
 * @param cmd_count 
 */
void	wait_for_child(t_shell *ms, int cmd_count)
{
	int	status;
	int	i;
	int	interrupted;

	i = 0;
	status = 0;
	interrupted = 0;
	while (i < cmd_count && interrupted == 0)
	{
		waitpid(ms->pid[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            interrupted = 1;
		i++;
	}
	handle_child_signal(status);
}

void	write_inside_pipe(int *heredoc_fd, char *line)
{
	write(heredoc_fd[1], line, ft_strlen(line));
	write(heredoc_fd[1], "\n", 1);
}

void	verify_comm_path(t_cmd *command, t_shell *ms)
{
	struct stat	file_stat;

	if (command->is_builtin == 1 && !command->comm_path)
	{
		ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		ft_putstr_fd(command->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit_shell(ms, 127);
	}
	if (stat(command->comm_path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			exit_shell(ms, 126);
		}
	}
}
