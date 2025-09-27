#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd(SHELL_NAME": Not prepared to handle arguments\n", 2);
		exit(1);
	}
}

void	init_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(ms));
	ms->prompt = SHELL_NAME"$ ";
	ms->input = NULL;
	ms->token = NULL;
	ms->exit_status = 0;
	ms->command = NULL;
	ms->envp = init_envp(envp);
	g_signal_number = 0;
}

void	exit_shell(int exit_status)
{
	// TODO: free memory
	exit(exit_status);
}
