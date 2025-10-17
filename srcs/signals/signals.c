#include "minishell.h"

/* 
 * Signal handler for SIGINT (Ctrl+C).
 * Prints a newline, resets the readline prompt, and sets the global exit status
 * to 130.
 * This ensures the shell remains responsive and does not exit on Ctrl+C.
 */
void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_sigpipe(int sig)
{
	(void)sig;
	g_exit_status = 141;
}

void	set_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigpipe;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error setting SIGPIPE", errno);
}

void	reset_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGQUIT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGPIPE", errno);
}

void	ignore_signals(t_shell *ms)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error ignoring SIGINT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error ignoring SIGQUIT", errno);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error ignoring SIGPIPE", errno);
}
