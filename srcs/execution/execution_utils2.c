#include "minishell.h"

void	create_pipe(int	*pipefd, t_shell *ms)
{
	if (pipe(pipefd) != 0)
		exit_shell(ms, 1);
}
