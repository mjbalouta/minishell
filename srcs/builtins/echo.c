#include "minishell.h"

void	builtin_echo(t_shell *ms, char **args)
{
	int	i;
	int	new_line;

	(void)ms;
	i = 1;
	new_line = 1;
	while (args && args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		new_line = 0;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	g_exit_status = 0;
}
