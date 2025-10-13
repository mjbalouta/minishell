#include "minishell.h"

int	init_envp(t_shell *ms, char **envp)
{
	int		i;
	t_envp	*head;
	char	*equal_ptr;
	char	*key;
	char	*value;

	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		equal_ptr = ft_strchr(envp[i], '=');
		if (equal_ptr)
		{
			key = ft_substr(envp[i], 0, equal_ptr - envp[i]);
			value = ft_strdup(equal_ptr + 1);
			if (!key || !value)
				return (free(key), free(value), -1);
			if (add_envp(key, value, &head) != 0)
				return (free(key), free(value), -1);
			free(key);
			free(value);
		}
		i++;
	}
	if (set_minimal_env(&head) != 0)
		print_error_and_exit(ms, "Memory allocation error", EXIT_FAILURE);
	ms->envp = head;
	return (0);
}

static void	print_warning_shlvl(char *arg)
{
	ft_putstr_fd(SHELL_NAME": warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

int	set_minimal_env(t_envp **lst)
{
	char	*path;
	int		ret;
	int		shlvl;
	char	*shlvl_ascii;

	path = getcwd(NULL, 0);
	if (!path)
		return (-1);
	ret = ft_setenv("PWD", path, false, lst);
	free(path);
	if (ret != 0)
		return (-1);
	shlvl = ft_atoi(ft_getenv2("SHLVL", *lst));
	shlvl_ascii = ft_itoa(shlvl + 1);
	if (!shlvl_ascii)
		return (-1);
	if (shlvl + 1 > 999)
	{
		print_warning_shlvl(shlvl_ascii);
		free(shlvl_ascii);
		shlvl_ascii = ft_itoa(1);
		if (!shlvl_ascii)
			return (-1);
	}
	ret = ft_setenv("SHLVL", shlvl_ascii, false, lst);
	free(shlvl_ascii);
	if (ret != 0)
		return (-1);
	return (0);
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
