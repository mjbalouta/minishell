#include "minishell.h"

void	builtin_unset(t_shell *ms, t_command *cmd)
{
	int		i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		ft_unsetenv(cmd->args[i], &ms->envp);
		i++;
	}
	g_exit_status = 0;
}
