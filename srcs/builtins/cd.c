/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:07:58 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/22 11:34:48 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_target(t_shell *ms, char **args, int *print_path)
{
	char	*path;

	*print_path = 0;
	if (!args[1] || !args[1][0])
	{
		path = ft_getenv("HOME", ms->envp);
		if (!path)
			print_error("cd: HOME not set");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_getenv("OLDPWD", ms->envp);
		if (!path)
			print_error("cd: OLDPWD not set");
		else
			*print_path = 1;
	}
	else
		path = args[1];
	return (path);
}

static void	print_error_cd(char *arg)
{
	ft_putstr_fd(SHELL_NAME": cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
}

static void	update_pwd_vars(t_shell *ms, int print_path)
{
	char	*pwd;

	ft_strlcpy(ms->oldpwd, ms->pwd, sizeof(ms->oldpwd));
	if (!ms->ignore_oldpwd)
		ft_setenv("OLDPWD", ms->oldpwd, false, &ms->envp);
	if (getcwd(ms->pwd, sizeof(ms->pwd)))
	{
		pwd = ft_strdup(ms->pwd);
		if (pwd)
		{
			if (ft_checkenv("PWD", ms->envp))
				ft_setenv("PWD", pwd, false, &ms->envp);
			free(pwd);
		}
	}
	if (print_path)
		ft_putendl_fd(ms->pwd, STDOUT_FILENO);
}

void	builtin_cd(t_shell *ms, t_cmd *cmd)
{
	char	*path;
	int		print_path;

	(void)ms;
	if (cmd->args && cmd->args[1] && ft_strncmp(cmd->args[1], "-", 1) == 0)
	{
		if (cmd->args[1][1] != '\0')
		{
			print_error("cd: options aren't supported");
			g_exit_status = 2;
			return ;
		}
	}
	g_exit_status = 1;
	if (cmd->args && cmd->args[1] && cmd->args[2])
		return (print_error("cd: too many arguments"));
	path = get_cd_target(ms, cmd->args, &print_path);
	if (!path)
		return ;
	if (chdir(path) != 0)
		return (print_error_cd(cmd->args[1]));
	update_pwd_vars(ms, print_path);
	g_exit_status = 0;
	return ;
}
