#include "minishell.h"

void	builtin_unset(t_shell *ms, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-", 1) == 0)
		{
			print_error("unset: options aren't supported");
			g_exit_status = 2;
			return ;
		}
		i++;
	}
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		ft_unsetenv(cmd->args[i], &ms->envp);
		i++;
	}
	g_exit_status = 0;
}
