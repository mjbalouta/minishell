#include "minishell.h"

/**
 * @brief defines fds for dup2 when input redirection is found
 * 
 * @param prev_fd 
 * @param ms 
 * @param pipefd 
 * @param i 
 */
void	handle_input_redir(t_shell *ms, int *pipefd, int i, t_redir *redir)
{
	int	in_fd;

	in_fd = -1;
	in_fd = open(redir->filename, O_RDONLY);
	if (in_fd < 0)
	{
		perror(redir->filename);
		exit_shell(ms, 1);
	}
	if (i >= 0 && i < (ms->nr_commands - 1))
	{
		dup2(in_fd, STDIN_FILENO);
		if (!redir->next)
			dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(in_fd, STDIN_FILENO);
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
void	handle_output_redir(int prev_fd, t_shell *ms, int i, t_redir *redir)
{
	int	out_fd;

	out_fd = -1;
	if (redir->type == T_REDIRECT_OUTPUT)
		out_fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_REDIR_OUTPUT_APPEND)
		out_fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror(redir->filename);
		exit_shell(ms, 1);
	}
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!redir->next)
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

/**
 * @brief tracks if there are redirections or not in the commands and calls
 * the needed function to define fds for communication between pipes
 * 
 * @param comm 
 * @param pipefd 
 */
void	handle_redir(t_shell *ms, int *pipefd, int prev_fd, int i, t_command *command)
{
	t_redir	*temp_redir;

	temp_redir = command->redir;
	if (temp_redir)
	{
		while (temp_redir)
		{
			if (temp_redir->type == T_REDIRECT_INPUT)
			{
				verify_comm_path(command, ms);
				handle_input_redir(ms, pipefd, i, temp_redir);
			}
			else if (temp_redir->type == T_REDIRECT_OUTPUT || temp_redir->type == T_REDIR_OUTPUT_APPEND)
			{
				verify_comm_path(command, ms);
				handle_output_redir(prev_fd, ms, i, temp_redir);
			}
			else if (temp_redir->type == T_HEREDOC)
			{
				verify_comm_path(command, ms);
				dup2(command->heredoc_fd, STDIN_FILENO);
				close(command->heredoc_fd);
				if (i != ms->nr_commands - 1 && command->args[0])
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
			}
			temp_redir = temp_redir->next;
		}
	}
	else
	{
		verify_comm_path(command, ms);
		handle_without_redir(i, pipefd, prev_fd, ms);
	}
}
