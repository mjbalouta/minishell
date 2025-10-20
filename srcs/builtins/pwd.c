#include "minishell.h"

void	builtin_pwd(t_shell *ms, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-", 1) == 0)
		{
			print_error("pwd: options aren't supported");
			g_exit_status = 2;
			return ;
		}
		i++;
	}
	ft_putendl_fd(ms->cwd, STDOUT_FILENO);
	g_exit_status = 0;
}
