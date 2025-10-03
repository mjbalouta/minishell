#include "minishell.h"

void	ft_env(t_shell *ms, char **args)
{
	if (args && args[1])
	{
		print_error("env: options or arguments not supported");
		ms->exit_status = 1;
		return ;
	}
	print_array_of_char(ft_envp_lst_to_char_array(ms, false));
	ms->exit_status = 0;
}
