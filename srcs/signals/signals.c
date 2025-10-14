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
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	init_signals(void)
{
	struct sigaction	sa;

	// Handle SIGINT
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(errno);
	}

	// Ignore SIGQUIT
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(errno);
	}
}

void	reset_signals(t_shell *ms)
{
	struct sigaction	sa;

	// Reset SIGINT
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGINT", errno);

	// Reset SIGQUIT
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_and_exit(ms, "sigaction: error resetting SIGQUIT", errno);
}

void	handle_child_signal(int status)
{
	int sig;

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
