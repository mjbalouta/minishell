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
	prev_fd = open(ms->command->redirection->filename, O_RDONLY);
	if (prev_fd < 0)
	{
		perror(ms->command->redirection->filename);
		exit_shell(ms, 1);
	}
	if (i >= 0 && i < (ms->nr_commands - 1))
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!ms->command->redirection->next)
			dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(prev_fd, STDIN_FILENO);
}
/**
 * @brief defines fds for dup2 when output redirection is found (output or append)
 * 
 * @param prev_fd 
 * @param ms 
 * @param out_fd 
 * @param i 
 */
void	handle_output_redir(int prev_fd, t_shell *ms, int out_fd, int i)
{
	if (ms->command->redirection->type == T_REDIRECT_OUTPUT)
		out_fd = open(ms->command->redirection->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (ms->command->redirection->type == T_REDIRECT_OUTPUT_APPEND)
		out_fd = open(ms->command->redirection->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror(ms->command->redirection->filename);
		exit_shell(ms, 1);
	}
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!ms->command->redirection->next)
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

void	handle_heredoc_input()
{
	
}

/**
 * @brief tracks if there are redirections or not in the commands and calls
 * the needed function to define fds for communication between pipes
 * 
 * @param comm 
 * @param pipefd 
 */
void	define_fds(t_shell *ms, int *pipefd, int prev_fd, int i)
{
	int	out_fd;

	out_fd = -1;
	if (ms->command->redirection)
	{
		while (ms->command->redirection)
		{
			if (ms->command->redirection->type == T_REDIRECT_INPUT)
				handle_input_redir(prev_fd, ms, pipefd, i);
			else if (ms->command->redirection->type == T_REDIRECT_OUTPUT || ms->command->redirection->type == T_REDIRECT_OUTPUT_APPEND)
				handle_output_redir(prev_fd, ms, out_fd, i);
			else if (ms->command->redirection->type == T_HEREDOC)
				handle_heredoc_input();
			ms->command->redirection = ms->command->redirection->next;
		}
	}
	else
		handle_without_redir(i, pipefd, prev_fd, ms);
}
