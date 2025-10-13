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
	if (getcwd(ms->cwd, sizeof(ms->cwd)) == NULL)
		print_error_and_exit(ms, "getcwd failed", EXIT_FAILURE);
}

void	free_shell(t_shell *ms)
{
	ft_envp_lstclear(&ms->envp);
	free(ms->input);
	ft_token_lstclear(&ms->token);
	if (ms->command)
		ft_cmd_lstclear(&ms->command);
	if (ms->pid)
	{
		free(ms->pid);
		ms->pid = NULL;
	}
	if (ms->in_fd > 2)
		close(ms->in_fd);
	if (ms->out_fd > 2)
		close(ms->out_fd);
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
	ft_putstr_fd(SHELL_NAME": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
