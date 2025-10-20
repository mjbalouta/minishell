#include "minishell.h"

/**
 * @brief defines fds for dup2 when input redirection is found
 * 
 * @param prev_fd 
 * @param ms 
 * @param pipefd 
 * @param i 
 */
void	handle_input_redir(t_shell *ms, int *pipefd, t_redir *redir, t_cmd *cmd)
{
	int	in_fd;

	in_fd = -1;
	in_fd = open(redir->filename, O_RDONLY);
	if (in_fd < 0)
	{
		ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		perror(redir->filename);
		close_both_fds(pipefd[0], pipefd[1]);
		exit_shell(ms, 1);
	}
	if (redir == cmd->last_in_redir)
	{
		if (ms->i >= 0 && ms->i < (ms->nr_commands - 1))
		{
			dup2(in_fd, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		else
			dup2(in_fd, STDIN_FILENO);
	}
	if (in_fd != -1)
		close(in_fd);
}

/**
 * @brief defines fds for dup2 when output redirection is found
 * (output or append)
 * 
 * @param prev_fd 
 * @param ms 
 * @param out_fd 
 * @param i 
 */
void	handle_out_redir(t_shell *ms, t_redir *redir, t_cmd *cmd, int *pipefd)
{
	int	out_fd;

	out_fd = -1;
	if (redir->type == T_REDIRECT_OUTPUT)
		out_fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_REDIR_OUT_APPEND)
		out_fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
	{
		ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		perror(redir->filename);
		close_both_fds(pipefd[0], pipefd[1]);
		exit_shell(ms, 1);
	}
	if (redir == cmd->last_out_redir || redir == cmd->last_append_redir)
	{
		if (ms->i > 0 && cmd->heredoc_fd == -1)
			dup2(ms->prev_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);
	}
	if (out_fd != -1)
		close(out_fd);
}

/**
 * @brief defines fds for dup2 when there are no redirections
 * 
 * @param i 
 * @param pipefd 
 * @param prev_fd 
 * @param ms 
 */
void	handle_without_redir(int *pipefd, t_shell *ms)
{
	if (ms->i == 0 && ms->i != (ms->nr_commands - 1))
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (ms->i > 0 && ms->i < (ms->nr_commands - 1))
	{
		dup2(ms->prev_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
		dup2(ms->prev_fd, STDIN_FILENO);
}

/**
 * @brief defines fds for heredoc redirect
 * 
 * @param ms 
 * @param command 
 * @param pipefd 
 */
void	handle_heredoc_redir(t_shell *ms, t_cmd *command, int *pipefd)
{
	dup2(command->heredoc_fd, STDIN_FILENO);
	close(command->heredoc_fd);
	if (ms->nr_commands > 1 && ms->i != ms->nr_commands - 1 && command->args[0])
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

/**
 * @brief tracks if there are redirections or not in the commands and calls
 * the needed function to define fds for communication between pipes
 * 
 * @param comm 
 * @param pipefd 
 */
void	handle_redir(t_shell *ms, int *pipefd, t_cmd *command)
{
	t_redir	*temp_redir;

	if (!command->redir)
	{
		handle_without_redir(pipefd, ms);
		return ;
	}
	define_last_redirection(command);
	temp_redir = command->redir;
	while (temp_redir)
	{
		if (temp_redir->type == T_REDIRECT_INPUT)
			handle_input_redir(ms, pipefd, temp_redir, command);
		else if (temp_redir->type == T_REDIRECT_OUTPUT
			|| temp_redir->type == T_REDIR_OUT_APPEND)
			handle_out_redir(ms, temp_redir, command, pipefd);
		else if (temp_redir->type == T_HEREDOC)
			handle_heredoc_redir(ms, command, pipefd);
		temp_redir = temp_redir->next;
	}
}
