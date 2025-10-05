#include "minishell.h"

void    disable_echoctl(void)
{
	struct termios  term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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
	disable_echoctl();
	init_signals();
	ms->prompt = SHELL_NAME"$ ";
	ms->input = NULL;
	ms->token = NULL;
	ms->command = NULL;
	ms->pid = NULL;
	if (init_envp(ms, envp) != 0)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
}

void	free_shell(t_shell *ms)
{
	// TODO: Free allocated memory before exiting
	if (ms->full_envp)
		free_char_array(ms->full_envp);
	ft_envp_lstclear(&ms->envp);
	free(ms->input);
	ft_token_lstclear(&ms->token);
	if (ms->command)
		ft_cmd_lstclear(&ms->command);
	if (ms->pid)
		free(ms->pid);
}

void	exit_shell(t_shell *ms, int exit_status)
{
	free_shell(ms);
	exit(exit_status);
}

void	print_error_and_exit(t_shell *ms, char *message, int exit_status)
{
	print_error(message);
	exit_shell(ms, exit_status);
}

void	print_error(char *message)
{
	ft_putstr_fd(SHELL_NAME": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
