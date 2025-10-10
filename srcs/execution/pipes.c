#include "minishell.h"

/**
 * @brief main part of the execution of each command
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(int *pipefd, t_shell *ms, int prev_fd, t_command *command)
{
	handle_redir(ms, pipefd, prev_fd, command);
	if (prev_fd != -1)
		close (prev_fd);
	if (ms->i < ms->nr_commands - 1)
		close(pipefd[1]);
	if (!command->args[0])
		exit_shell(ms, 0);
	verify_comm_path(command, ms);
	if (command->is_builtin == 0)
	{
		execute_builtin(ms, command);
		exit_shell(ms, 0);
	}
	else
	{
		if (execve(command->comm_path, command->args, ms->full_envp) == -1)
		{
			perror(command->args[0]);
			exit_shell(ms, 1);
		}
	}
}

/**
 * @brief executes the commands either on the parent process or forks
 * childs to execute them
 * 
 * @param ms 
 */
void	handle_processes(t_shell *ms)
{
	int			pipefd[2];
	int			id;
	int			prev_fd;
	t_command	*temp;

	id = 0;
	prev_fd = -1;
	temp = ms->command;
	if (ms->nr_commands == 1 && temp->is_builtin == 0)
	{
		handle_redir(ms, pipefd, prev_fd, temp);
		execute_builtin(ms, temp);
	}
	else
	{
		while (++ms->i < ms->nr_commands && temp)
		{
			if (ms->i < ms->nr_commands - 1)
				create_pipe(pipefd, ms);
			if (temp->redir && temp->redir->type == T_HEREDOC)
				handle_heredoc_input(temp, ms);
			// if (temp->args[0])
			// {
			ms->pid[id] = fork();
			if (ms->pid[id] < 0)
				exit_shell(ms, 1);
			if (ms->pid[id++] == 0)
				execute_pipe_cmd(pipefd, ms, prev_fd, temp);
			// }
			if (ms->i < ms->nr_commands - 1)
			{
				if (pipefd[1] != -1)
					close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			temp = temp->next;
		}
		if (prev_fd != -1)
			close(prev_fd);
		g_exit_status = wait_for_child(ms, id);
	}
}

/**
 * @brief main execution function
 * 
 * @param ms 
 */
void	execute(t_shell *ms)
{
	t_command	*temp;

	ms->full_envp = ft_envp_lst_to_char_array(ms, false);
	temp = ms->command;
	init_pids_container(ms);
	verify_if_bultin(ms);
	while (temp)
	{
		if (temp->is_builtin == 1)
			fill_path(ms, temp);
		temp = temp->next;
	}
	ms->nr_commands = count_commands(ms);
	ms->i = -1;
	handle_processes(ms);
	free(ms->pid);
	free_char_array(ms->full_envp);
}
