#include "minishell.h"

void	builtin_echo(t_shell *ms, t_command *cmd)
{
	int	i;
	int	new_line;

	(void)ms;
	i = 1;
	new_line = 1;
	while (cmd->args && cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 0;
}
