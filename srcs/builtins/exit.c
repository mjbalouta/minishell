#include "minishell.h"

static int	check_arg_is_int(char *nptr)
{
	long	value;
	int		signal;

	value = 0;
	signal = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
		if (*nptr < '0' || *nptr > '9')
			return (EXIT_FAILURE);
	}
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			value = value * 10 + *nptr++ - '0';
		else
			return (EXIT_FAILURE);
		if (((value * signal) > INT_MAX) || ((value * signal) < INT_MIN))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	normalized_exit_status(int exit_status)
{
	if (exit_status < 0)
		return (256 + (exit_status % 256));
	else if (exit_status > 255)
		return (exit_status % 256);
	else
		return (exit_status);
}

void	ft_exit(t_shell *ms, char **args)
{
	if (args && args[2])
	{
		print_error("exit: too many arguments");
		g_exit_status = 1;
		return ;
	}
	ft_putendl_fd("exit", 1);
	if (args && args[1])
	{
		if (check_arg_is_int(args[1]) != EXIT_SUCCESS)
		{
			// TODO: change message to match bash error message
			print_error("exit: numeric argument required");
			g_exit_status = 255;
		}
		else
			g_exit_status = (unsigned char)(ft_atoi(args[1]));
	}
	exit_shell(ms, normalized_exit_status(g_exit_status));
}
