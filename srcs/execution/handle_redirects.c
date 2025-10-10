#include "minishell.h"

/**
 * @brief defines fds for dup2 when input redirection is found
 * 
 * @param prev_fd 
 * @param ms 
 * @param pipefd 
 * @param i 
 */
void	handle_input_redir(t_shell *ms, int *pipefd, t_redir *redir)
{
	int	in_fd;

	in_fd = -1;
	in_fd = open(redir->filename, O_RDONLY);
	if (in_fd < 0)
	{
		perror(redir->filename);
		exit_shell(ms, 1);
	}
	if (ms->i >= 0 && ms->i < (ms->nr_commands - 1))
	{
		dup2(in_fd, STDIN_FILENO);
		if (!redir->next)
			dup2(pipefd[1], STDOUT_FILENO);
	}
	else
		dup2(in_fd, STDIN_FILENO);
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
void	handle_output_redir(int prev_fd, t_shell *ms, t_redir *redir)
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
	if (ms->i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		if (!redir->next)
			dup2(out_fd, STDOUT_FILENO);
	}
	else
		dup2(out_fd, STDOUT_FILENO);
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
void	handle_without_redir(int *pipefd, int prev_fd, t_shell *ms)
{
    if (ms->i == 0 && ms->i != (ms->nr_commands - 1))
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    else if (ms->i > 0 && ms->i < (ms->nr_commands - 1))
    {
        dup2(prev_fd, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        // close(pipefd[1]);
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
void	handle_redir(t_shell *ms, int *pipefd, int prev_fd, t_command *command)
{
	t_redir	*temp_redir;

	temp_redir = command->redir;
	while (temp_redir)
		{
			if (temp_redir->type == T_REDIRECT_INPUT)
				handle_input_redir(ms, pipefd, temp_redir);
			else if (temp_redir->type == T_REDIRECT_OUTPUT || temp_redir->type == T_REDIR_OUTPUT_APPEND)
				handle_output_redir(prev_fd, ms, temp_redir);
			else if (temp_redir->type == T_HEREDOC)
			{
				dup2(command->heredoc_fd, STDIN_FILENO);
				close(command->heredoc_fd);
				if (ms->nr_commands > 1 && ms->i != ms->nr_commands - 1 && command->args[0])
				{
					dup2(pipefd[1], STDOUT_FILENO);
					// close(pipefd[1]);
				}
			}
			temp_redir = temp_redir->next;
		}
	if (!temp_redir)
		handle_without_redir(pipefd, prev_fd, ms);
}
