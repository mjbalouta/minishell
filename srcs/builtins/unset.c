#include "minishell.h"

void	builtin_unset(t_shell *ms, char **args)
{
	(void)ms;
	(void)args;
	g_exit_status = 0;
}
