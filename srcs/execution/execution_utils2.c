#include "minishell.h"

void	create_pipe(int	*pipefd, t_shell *ms)
{
	if (pipe(pipefd) != 0)
		exit_shell(ms, 1);
}

void	close_one_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	close_both_fds(int fd1, int fd2)
{
	close_one_fd(fd1);
	close_one_fd(fd2);
}

void	free_pid(t_shell *ms)
{
	if (ms->pid)
	{
		free(ms->pid);
		ms->pid = NULL;
	}
}

void	handle_execve_error(t_cmd *command, char **envp, t_shell *ms)
{
	if (errno == EACCES || errno == EISDIR)
	{
		// ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 126);
	}
	else if (errno == ENOENT || errno == ENOTDIR)
	{
		// ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 127);
	}
	else
	{
		// ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
		perror(command->args[0]);
		free_char_array(envp);
		exit_shell(ms, 1);
	}
}
