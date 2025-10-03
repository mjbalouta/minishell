#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		print_error("Not prepared to handle arguments");
		exit(EXIT_FAILURE);
	}
}

void	init_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(ms));
	init_signals();
	ms->prompt = SHELL_NAME"$ ";
	ms->input = NULL;
	ms->token = NULL;
	ms->exit_status = 0;
	ms->command = NULL;
	ms->pid = NULL;
	if (init_envp(ms, envp) != 0)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	g_signal_number = 0;
}

void	exit_shell(t_shell *ms, int exit_status)
{
	free(ms->input);
	ft_envp_lstclear(&ms->envp);
	ft_token_lstclear(&ms->token);
	if (ms->command)
		ft_cmd_lstclear(&ms->command);
	if (ms->pid)
		free(ms->pid);
	exit(exit_status);
}

void	print_error_and_exit(t_shell *ms, char *message, int exit_status)
{
	ft_putstr_fd(SHELL_NAME": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit_shell(ms, exit_status);
}

void	print_error(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
