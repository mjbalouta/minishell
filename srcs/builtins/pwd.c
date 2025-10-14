#include "minishell.h"

void	builtin_pwd(t_shell *ms, t_cmd *cmd)
{
	// char	*path;

	(void)cmd->args;
	// path = getcwd(NULL, 0);
	// if (!path)
	// 	print_error_and_exit(ms, "getcwd failed", errno);
	ft_putendl_fd(ms->cwd, STDOUT_FILENO);
	// free(path);
	g_exit_status = 0;
}
