/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/11/12 16:29:57 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_key_value(char *key, char *value);

int	init_envp(t_shell *ms, char **envp)
{
	int		i;
	char	*equal_ptr;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		equal_ptr = ft_strchr(envp[i], '=');
		if (equal_ptr)
		{
			key = ft_substr(envp[i], 0, equal_ptr - envp[i]);
			value = ft_strdup(equal_ptr + 1);
			if (!key || !value)
				return (free_key_value(key, value), -1);
			if (add_envp(key, value, &ms->envp) != 0)
				return (free_key_value(key, value), -1);
			free_key_value(key, value);
		}
		i++;
	}
	if (set_minimal_env(&ms->envp) != EXIT_SUCCESS)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	return (0);
}

static void	print_warning_shlvl(char *arg)
{
	ft_putstr_fd(SHELL_NAME": warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

static int	set_pwd_env(t_envp **lst)
{
	char	*path;
	int		ret;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	ret = ft_setenv("PWD", path, false, lst);
	free(path);
	if (ret != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_minimal_env(t_envp **lst)
{
	int		ret;
	int		shlvl;
	char	*shlvl_ascii;

	if (set_pwd_env(lst) != 0)
		return (-1);
	shlvl = ft_atoi(ft_getenv2("SHLVL", *lst));
	shlvl_ascii = ft_itoa(shlvl + 1);
	if (!shlvl_ascii)
		return (EXIT_FAILURE);
	if (shlvl + 1 > 999)
	{
		print_warning_shlvl(shlvl_ascii);
		free(shlvl_ascii);
		shlvl_ascii = ft_itoa(1);
		if (!shlvl_ascii)
			return (EXIT_FAILURE);
	}
	ret = ft_setenv("SHLVL", shlvl_ascii, false, lst);
	free(shlvl_ascii);
	if (ret != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	add_envp(char *key, char *value, t_envp **lst)
{
	t_envp	*envp;

	envp = ft_envp_lstnew(key, value);
	if (!envp)
		return (-1);
	ft_envp_lstadd_back(lst, envp);
	return (0);
}
