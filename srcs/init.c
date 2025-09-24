#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		printf(SHELL_NAME": Not prepared to handle arguments\n");
		exit(0);
	}
}

void	init(t_shell *ms, char **envp)
{
	init_envp(ms, envp);
	ms->prompt = SHELL_NAME": ";
	ms->input = NULL;
	ms->token = NULL;
	ms->exit_status = 0;
	g_signal_number = 0;
	ms->command = NULL;
}