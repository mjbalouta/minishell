#include "minishell.h"

/**
 * @brief defines fds for dup2 when input redirection is found
 * 
 * @param prev_fd 
 * @param ms 
 * @param pipefd 
 * @param i 
 */
void	handle_input_redir(int prev_fd, t_shell *ms, int *pipefd, int i)
{
	verify_comm_path(ms);
	prev_fd = open(ms->command->redir->filename, O_RDONLY);
	if (prev_fd < 0)
	{
		perror(ms->command->redir->filename);
		exit_shell(ms, 1);
	}
	if (i >= 0 && i < (ms->nr_commands - 1))
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!ms->command->redir->next)
			dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(prev_fd, STDIN_FILENO);
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
void	handle_output_redir(int prev_fd, t_shell *ms, int i)
{
	int	out_fd;

	out_fd = -1;
	verify_comm_path(ms);
	if (ms->command->redir->type == T_REDIRECT_OUTPUT)
		out_fd = open(ms->command->redir->filename, O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
	else if (ms->command->redir->type == T_REDIR_OUTPUT_APPEND)
		out_fd = open(ms->command->redir->filename, O_CREAT
				| O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror(ms->command->redir->filename);
		exit_shell(ms, 1);
	}
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!ms->command->redir->next)
			dup2(out_fd, STDOUT_FILENO);
	}
	else
		dup2(out_fd, STDOUT_FILENO);
}

/**
 * @brief defines fds for dup2 when there are no redirections
 * 
 * @param i 
 * @param pipefd 
 * @param prev_fd 
 * @param ms 
 */
void	handle_without_redir(int i, int *pipefd, int prev_fd, t_shell *ms)
{
	verify_comm_path(ms);
	if (i == 0 && i != (ms->nr_commands - 1))
		dup2(pipefd[1], STDOUT_FILENO);
	if (i > 0 && i < (ms->nr_commands - 1))
	{
		dup2(prev_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(prev_fd, STDIN_FILENO);
}

/**
 * @brief tracks if there are redirections or not in the commands and calls
 * the needed function to define fds for communication between pipes
 * 
 * @param comm 
 * @param pipefd 
 */
void	handle_redir(t_shell *ms, int *pipefd, int prev_fd, int i)
{
	if (ms->command->redir)
	{
		while (ms->command->redir)
		{
			if (ms->command->redir->type == T_REDIRECT_INPUT)
				handle_input_redir(prev_fd, ms, pipefd, i);
			else if (ms->command->redir->type == T_REDIRECT_OUTPUT
				|| ms->command->redir->type == T_REDIR_OUTPUT_APPEND)
				handle_output_redir(prev_fd, ms, i);
			else if (ms->command->redir->type == T_HEREDOC)
			{
				dup2(ms->command->heredoc_fd, STDIN_FILENO);
				close(ms->command->heredoc_fd);
				if (i != ms->nr_commands - 1 && ms->command->args[0])
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
			}
			ms->command->redir = ms->command->redir->next;
		}
	}
	else
		handle_without_redir(i, pipefd, prev_fd, ms);
}
