#include "minishell.h"

/**
 * @brief main part of the execution of each command
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(int *pipefd, t_shell *ms, int prev_fd, t_cmd *command)
{
	char		**envp;

	handle_redir(ms, pipefd, prev_fd, command);
	close_one_fd(prev_fd);
	if (ms->i < ms->nr_commands - 1)
		close_both_fds(pipefd[0], pipefd[1]);
	if (!command->args[0])
		exit_shell(ms, 0);
	verify_comm_path(command, ms);
	reset_signals(ms);
	if (command->is_builtin == 0)
	{
		execute_builtin(ms, command);
		exit_shell(ms, 0);
	}
	else
	{
		envp = ft_envp_lst_to_char_array(ms, false);
		if (execve(command->comm_path, command->args, envp) == -1)
			handle_execve_error(command, envp, ms);
	}
}

void	exec_single_builtin(t_cmd *cmd, t_shell *ms, int prev_fd, int *pipefd)
{
	// if (cmd->redir && cmd->redir->type == T_HEREDOC)
	// 	handle_heredoc_input(cmd, ms);
	handle_redir(ms, pipefd, prev_fd, cmd);
	execute_builtin(ms, cmd);
}

/**
 * @brief executes the commands either on the parent process or forks
 * childs to execute them
 * 
 * @param ms 
 */
void	handle_child_processes(t_shell *ms, int *pipefd, int prev_fd, int id)
{
	t_cmd	*temp;

	temp = ms->command;
	ms->i = -1;
	while (++ms->i < ms->nr_commands && temp)
	{
		if (ms->i < ms->nr_commands - 1)
			create_pipe(pipefd, ms);
		// if (temp->redir && temp->redir->type == T_HEREDOC)
		// 	handle_heredoc_input(temp, ms);
		ms->pid[id] = fork();
		if (ms->pid[id] < 0)
			exit_shell(ms, 1);
		if (ms->pid[id++] == 0)
			execute_pipe_cmd(pipefd, ms, prev_fd, temp);
		close_one_fd(prev_fd);
		if (ms->i < ms->nr_commands - 1)
		{
			close_one_fd(pipefd[1]);
			prev_fd = pipefd[0];
		}
		temp = temp->next;
	}
	close_one_fd(prev_fd);
	ignore_signals(ms);
	wait_for_child(ms, id);
	set_signals(ms);
}

/**
 * @brief main execution function
 * 
 * @param ms 
 */
void	execute(t_shell *ms)
{
	t_cmd	*temp;
	int		pipefd[2];
	int		prev_fd;
	int		id;

	temp = ms->command;
	prev_fd = -1;
	id = 0;
	while (temp)
	{
		g_exit_status = 0;
		verify_if_bultin(temp);
		if (temp->is_builtin == 1)
			fill_path(ms, temp);
		if (temp->redir && temp->redir->type == T_HEREDOC)
		{
			handle_heredoc_input(temp, ms);
			if (g_exit_status == 130)
				return ;
		}
		temp = temp->next;
	}
	ms->nr_commands = count_commands(ms);
	init_pids_container(ms);
	temp = ms->command;
	if (ms->nr_commands == 1 && temp->is_builtin == 0)
		exec_single_builtin(temp, ms, prev_fd, pipefd);
	else
		handle_child_processes(ms, pipefd, prev_fd, id);
	free_pid(ms);
}
