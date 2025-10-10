#include "minishell.h"

void	builtin_env(t_shell *ms, t_command *cmd)
{
	if (cmd->args && cmd->args[1])
	{
		print_error("env: options or arguments not supported");
		g_exit_status = 1;
		return ;
	}
	print_array_of_char(ft_envp_lst_to_char_array(ms, false));
	g_exit_status = 0;
}
