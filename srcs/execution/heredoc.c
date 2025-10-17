#include "minishell.h"

/**
 * @brief find last heredoc (used to store in the pipe only the output
 * of this last one)
 * 
 * @param redir_list 
 * @return t_redir* last_heredoc 
 */
t_redir	*find_last_redir(t_redir *redir_list, t_token_type redirection)
{
	t_redir	*last_redirection;

	last_redirection = NULL;
	while (redir_list)
	{
		if (redir_list->type == redirection)
			last_redirection = redir_list;
		redir_list = redir_list->next;
	}
	return (last_redirection);
}

/**
 * @brief reads from the stdin and compares the line with the limiter(filename),
 * also calls the function to write the output of the last_heredoc to the pipe
 * 
 * @param redir_list 
 * @param last_here 
 * @param heredoc_fd 
 */
void	read_heredoc(t_redir *redir_list, t_redir *last_here, int *heredoc_fd)
{
	char	*line;
    struct sigaction sa_new;
    struct sigaction sa_old;

	ft_bzero(&sa_new, sizeof(sa_new));
	ft_bzero(&sa_old, sizeof(sa_old));
	sa_new.sa_handler = handle_sigint_heredoc;
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sigaction(SIGINT, &sa_new, &sa_old);

	line = NULL;
	if (redir_list->type == T_HEREDOC)
	{
		while (true)
		{
			line = readline("> ");
			if (g_exit_status == 130)
			{
				sigaction(SIGINT, &sa_old, NULL);
				free(line);
				return ;
			}
			if (!line)
			{
				print_error("warning: here-document delimited by end-of-file");
				sigaction(SIGINT, &sa_old, NULL);
				return ;
			}
			if (ft_strcmp(line, redir_list->filename) == 0)
			{
				sigaction(SIGINT, &sa_old, NULL);
				free(line);
				return ;
			}
			if (redir_list == last_here)
				write_inside_pipe(heredoc_fd, line);
			free(line);
		}
	}
	sigaction(SIGINT, &sa_old, NULL);
}

/**
 * @brief handles heredoc input calling other useful functions - stores
 * the read end of the pipe in a variable for it to be the input of the
 * command of that redirection
 * 
 * @param ms 
 */
void	handle_heredoc_input(t_cmd *command, t_shell *ms)
{
	int		heredoc_fd[2];
	t_redir	*redir_list;
	t_redir	*last_heredoc;

	redir_list = command->redir;
	last_heredoc = find_last_redir(redir_list, T_HEREDOC);
	redir_list = command->redir;
	if (last_heredoc && pipe(heredoc_fd) != 0)
		exit_shell(ms, 1);
	while (redir_list)
	{
		if (redir_list->type == T_HEREDOC)
			read_heredoc(redir_list, last_heredoc, heredoc_fd);
		redir_list = redir_list->next;
	}
	if (last_heredoc)
	{
		close(heredoc_fd[1]);
		command->heredoc_fd = heredoc_fd[0];
	}
}
