#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
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
		print_error("Error changing signals action");
		exit(EXIT_FAILURE);
	}

	// Ignore SIGQUIT
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		print_error("Error changing signals action");
		exit(EXIT_FAILURE);
	}
}
