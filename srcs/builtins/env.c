#include "minishell.h"

void	execute_env(t_shell *ms, char **args)
{
	if (args && args[1])
	{
		print_error("env: options or arguments not supported");
		g_exit_status = 1;
		return ;
	}
	print_array_of_char(ft_envp_lst_to_char_array(ms, false));
	g_exit_status = 0;
}
