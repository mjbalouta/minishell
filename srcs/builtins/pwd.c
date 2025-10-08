#include "minishell.h"

void	builtin_pwd(t_shell *ms, char **args)
{
	char	*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (!path)
		print_error_and_exit(ms, "getcwd failed", errno);
	ft_putendl_fd(path, 1);
	free(path);
	g_exit_status = 0;
}
