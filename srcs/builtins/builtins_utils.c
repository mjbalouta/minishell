#include "minishell.h"

void	execute_builtin(t_shell *ms, char **args)
{
	if (ft_strcmp(ms->command->args[0], "echo") == 0)
		builtin_echo(ms, args);
	else if (ft_strcmp(ms->command->args[0], "cd") == 0)
		builtin_cd(ms, args);
	else if (ft_strcmp(ms->command->args[0], "pwd") == 0)
		builtin_pwd(ms, args);
	else if (ft_strcmp(ms->command->args[0], "export") == 0)
		builtin_export(ms, args);
	else if (ft_strcmp(ms->command->args[0], "unset") == 0)
		builtin_unset(ms, args);
	else if (ft_strcmp(ms->command->args[0], "env") == 0)
		builtin_env(ms, args);
	else if (ft_strcmp(ms->command->args[0], "exit") == 0)
		builtin_exit(ms, args);
}
