#include "minishell.h"

static bool	valid_n_option(char *arg, int *i)
{
	int	j;

	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (false);
		j++;
	}
	(*i)++;
	return (true);
}

void	builtin_echo(t_shell *ms, t_command *cmd)
{
	int		i;
	bool	new_line;
	bool	print_started;

	(void)ms;
	i = 1;
	new_line = true;
	print_started = false;
	while (cmd->args && cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], "-n", 2) == 0) && !print_started)
			if (valid_n_option(cmd->args[i], &i))
			{
				new_line = false;
				continue ;
			}
		print_started = true;
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 0;
}
