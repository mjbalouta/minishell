#include "minishell.h"

/**
 * @brief main part of the execution of each command
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(int *pipefd, int i, t_shell *ms, int prev_fd)
{
	handle_redir(ms, pipefd, prev_fd, i);
	if (prev_fd != -1)
		close (prev_fd);
	if (i < ms->nr_commands - 1)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	// if (comm->is_builtin == 0)
	// 	select_builtin(ms);
	// else
	// {
	if (execve(ms->command->comm_path, ms->command->args, ms->full_envp) == -1)
	{
		perror(ms->command->args[0]);
		exit_shell(ms, 1);
	}
	// }
}

/**
 * @brief executes the commands either on the parent process or forks
 * childs to execute them
 * 
 * @param ms 
 */
void	handle_processes(t_shell *ms)
{
	int	i;
	int	pipefd[2];
	int	id;
	int	prev_fd;

	i = -1;
	id = 0;
	prev_fd = -1;
	// if (ms->nr_commands == 1 && ms->command->is_builtin == 0)
	// 	select_builtin(ms);
	// else
	// {
		while (++i < ms->nr_commands && ms->command)
		{
			if (i < ms->nr_commands - 1)
				create_pipe(pipefd, ms);
			if (ms->command->redir && ms->command->redir->type == T_HEREDOC)
				handle_heredoc_input(ms);
			if (ms->command->args[0])
			{
				ms->pid[id] = fork();
				if (ms->pid[id] < 0)
					exit_shell(ms, 1);
				if (ms->pid[id++] == 0)
					execute_pipe_cmd(pipefd, i, ms, prev_fd);
			}
			if (i < ms->nr_commands - 1)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			ms->command = ms->command->next;
		}
		if (prev_fd != -1)
			close(prev_fd);
		ms->exit_status = wait_for_child(ms, id);
	// }
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
	while (temp)
	{
		if (temp->is_builtin == 1)
			fill_path(ms, temp);
		temp = temp->next;
	}
	ms->nr_commands = count_commands(ms);
	handle_processes(ms);
	free(ms->pid);
	free_char_array(ms->full_envp);
}
