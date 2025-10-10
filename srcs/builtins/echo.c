#include "minishell.h"

void	builtin_echo(t_shell *ms, t_command *cmd)
{
	int	i;
	int	new_line;
	int fd = cmd->outfile;

	fd = 1;	// TODO: remove line
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
		ft_putstr_fd(cmd->args[i], fd);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", fd);
	g_exit_status = 0;
}
