#include "minishell.h"

void	builtin_unset(t_shell *ms, char **args)
{
	t_envp	*env;
	int		i;

	env = ms->envp;
	i = 1;
	while (args && args[i])
	{
		ft_unsetenv(args[i], &ms->envp);
		i++;
	}
	g_exit_status = 0;
}
