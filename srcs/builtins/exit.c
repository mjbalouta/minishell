/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:08:25 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:08:26 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespaces(char **str);
int		get_sign(char **str);

static int	check_arg_is_longlong(char *nptr)
{
	unsigned long long	v;
	int					s;
	int					d;

	v = 0;
	skip_whitespaces(&nptr);
	s = get_sign(&nptr);
	if (s == 0)
		return (EXIT_FAILURE);
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
		{
			d = *nptr++ - '0';
			if ((s == 1) && (v > ((unsigned long long)LLONG_MAX - d) / 10ULL))
				return (EXIT_FAILURE);
			if ((s != 1) && (v > ((unsigned long long)LLONG_MAX + 1ULL - d)
					/ 10ULL))
				return (EXIT_FAILURE);
			v = v * 10 + d;
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
	g_exit_status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->args && cmd->args[1])
	{
		if (ft_strcmp(cmd->args[1], "--") == 0)
			exit_shell(ms, 0);
		else
		{
			if (check_arg_is_longlong(cmd->args[1]) != EXIT_SUCCESS)
			{
				print_error_exit_arg(cmd->args[1]);
				exit_shell(ms, 2);
			}
			else
				g_exit_status = (unsigned char)(ft_atoll(cmd->args[1]));
		}
		if (cmd->args && cmd->args[2])
		{
			print_error("exit: too many arguments");
			g_exit_status = 1;
			return ;
		}
	}
	exit_shell(ms, normalized_exit_status(g_exit_status));
}
