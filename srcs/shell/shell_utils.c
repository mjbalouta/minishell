#include "minishell.h"

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	init_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(ms));
	set_signals(ms);
	ms->prompt = SHELL_NAME"$ ";
	ms->input = NULL;
	ms->token = NULL;
	ms->command = NULL;
	ms->pid = NULL;
	ms->i = 0;
	ms->nr_commands = 0;
	ms->envp = NULL;
	if (init_envp(ms, envp) != 0)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	if (getcwd(ms->cwd, sizeof(ms->cwd)) == NULL)
		print_error_and_exit(ms, "getcwd failed", EXIT_FAILURE);
}

void	free_shell(t_shell *ms)
{
	free(ms->input);
	ms->input = NULL;
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
	ft_envp_lstclear(&ms->envp);
	exit(exit_status);
}
