#include "minishell.h"

/**
 * @brief Executes pipe commands
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(int *pipefd, t_shell *ms, int prev_fd, t_cmd *command)
{
	char		**envp;

	handle_redir(ms, pipefd, command);
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

/**
 * @brief Executes single builtin commands
 * 
 * @param cmd 
 * @param ms 
 * @param prev_fd 
 * @param pipefd 
 */
void	exec_single_builtin(t_cmd *cmd, t_shell *ms, int *pipefd)
{
	handle_redir(ms, pipefd, cmd);
	execute_builtin(ms, cmd);
}

/**
 * @brief Executes the commands either on the parent process or forks
 * childs to execute them
 * 
 * @param ms 
 */
void	handle_child_processes(t_shell *ms, int *pipefd, int id)
{
	t_cmd	*temp;

	temp = ms->command;
	ms->i = -1;
	while (++ms->i < ms->nr_commands && temp)
	{
		if (ms->i < ms->nr_commands - 1)
			create_pipe(pipefd, ms);
		ms->pid[id] = fork();
		if (ms->pid[id] < 0)
			exit_shell(ms, 1);
		if (ms->pid[id++] == 0)
			execute_pipe_cmd(pipefd, ms, ms->prev_fd, temp);
		close_one_fd(ms->prev_fd);
		if (ms->i < ms->nr_commands - 1)
		{
			close_one_fd(pipefd[1]);
			ms->prev_fd = pipefd[0];
		}
		temp = temp->next;
	}
	close_one_fd(ms->prev_fd);
	ignore_signals(ms);
	wait_for_child(ms, id);
	set_signals(ms);
}

/**
 * @brief Processes commands before executing them: fill paths and
 * handle all possible heredocs
 * 
 * @param ms 
 */
int	process_before_executing(t_shell *ms)
{
	t_cmd	*cmd;

	cmd = ms->command;
	while (cmd)
	{
		g_exit_status = 0;
		verify_if_bultin(cmd);
		cmd->heredoc_fd = -1;
		if (cmd->is_builtin == 1)
			fill_path(ms, cmd);
		if (cmd->redir && cmd->redir->type == T_HEREDOC)
		{
			handle_heredoc_input(cmd, ms);
			if (g_exit_status == 130)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}

/**
 * @brief Main execution function
 * 
 * @param ms 
 */
int	execute(t_shell *ms)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		id;

	ms->prev_fd = -1;
	id = 0;
	if (process_tokens(ms) == -1)
		return (-1);
	if (process_before_executing(ms) == -1)
		return (-1);
	ms->nr_commands = count_commands(ms);
	init_pids_container(ms);
	cmd = ms->command;
	if (ms->nr_commands == 1 && cmd->is_builtin == 0)
		exec_single_builtin(cmd, ms, pipefd);
	else
		handle_child_processes(ms, pipefd, id);
	free_pid(ms);
	ft_cmd_lstclear(&ms->command);
	ft_token_lstclear(&ms->token);
	return (0);
}
