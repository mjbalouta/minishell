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

void	close_both_fds(int *fd)
{
	close_one_fd(fd[0]);
	close_one_fd(fd[1]);
}

void	free_pid(t_shell *ms)
{
	if (ms->pid)
	{
		free(ms->pid);
		ms->pid = NULL;
	}
}
