#include "minishell.h"

static int	check_arg_is_longlong(char *nptr)
{
	long long	value;
	int			signal;
	int 		 digit;

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
		{
			digit = *nptr++ - '0';
			if (signal == 1)
			{
				if (value > (LLONG_MAX - digit) / 10)
					return (EXIT_FAILURE);
			}
			else
			{
				if (value > (-(LLONG_MIN + digit)) / 10)
					return (EXIT_FAILURE);
			}
			value = value * 10 + digit;
		}
		else
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

static void	print_error_exit_arg(char *arg)
{
	ft_putstr_fd(SHELL_NAME": exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	builtin_exit(t_shell *ms, t_cmd *cmd)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->args && cmd->args[1])
	{
		if (ft_strcmp(cmd->args[1], "--") == 0)
		{
			g_exit_status = 0;
			exit_shell(ms, g_exit_status);
		}
		else
		if (check_arg_is_longlong(cmd->args[1]) != EXIT_SUCCESS)
		{
			print_error_exit_arg(cmd->args[1]);
			g_exit_status = 2;
			exit_shell(ms, g_exit_status);
		}
		else
			g_exit_status = (unsigned char)(ft_atoll(cmd->args[1]));
		if (cmd->args && cmd->args[2])
		{
			print_error("exit: too many arguments");
			g_exit_status = 1;
			return ;
		}
	}
	exit_shell(ms, normalized_exit_status(g_exit_status));
}
