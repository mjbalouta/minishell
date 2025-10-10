#include "minishell.h"

void	builtin_cd(t_shell *ms, t_command *cmd)
{
	(void)ms;
	if (cmd->args && cmd->args[2])
	{
		print_error("cd: too many arguments");
		g_exit_status = 1;
		return ;
	}

	g_exit_status = 0;
}
