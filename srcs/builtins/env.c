#include "minishell.h"

void	builtin_env(t_shell *ms, t_command *cmd)
{
	char	**array;

	if (cmd->args && cmd->args[1])
	{
		print_error("env: options or arguments not supported");
		g_exit_status = 1;
		return ;
	}
	array = ft_envp_lst_to_char_array(ms, false);
	print_array_of_char(array);
	free_char_array(array);
	g_exit_status = 0;
}
