#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd(SHELL_NAME": Not prepared to handle arguments\n", 2);
		exit(EXIT_FAILURE);
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
	ms->envp = init_envp(ms, envp);
	g_signal_number = 0;
}

void	exit_shell(t_shell *ms, int exit_status)
{
	// Free allocated memory before exiting
	free(ms->input);
	ft_envp_lstclear(&ms->envp);
	ft_token_lstclear(&ms->token);
	exit(exit_status);
}
