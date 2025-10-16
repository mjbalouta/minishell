#include "minishell.h"

/* 
 * Signal handler for SIGINT (Ctrl+C).
 * Prints a newline, resets the readline prompt, and sets the global exit status
 * to 130.
 * This ensures the shell remains responsive and does not exit on Ctrl+C.
 */
static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 130;
}

void	set_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
}

void	set_signals_heredoc(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
}

void	reset_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGQUIT", errno);
}

void	ignore_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error ignoring SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error ignoring SIGQUIT", errno);
}

void	handle_child_signal(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_exit_status = 130;
		}
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: (core dumped)\n", 1);
			g_exit_status = 131;
		}
		else
			g_exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
}
