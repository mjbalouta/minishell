#include "minishell.h"

static bool	is_valid_key_char(char c, int pos)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	if (pos > 0 && (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

static bool	is_valid_key(char *key)
{
	size_t	i;

	if (!key || !*key)
		return (false);
	i = 0;
	while (key[i])
	{
		if (!is_valid_key_char(key[i], i))
			return (false);
		i++;
	}
	return (true);
}

static void	print_error_export_arg(char *arg)
{
	ft_putstr_fd(SHELL_NAME": export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	process_export_arg(t_shell *ms, char *arg)
{
	t_envp	*env;
	char	*equal_ptr;
	char	*key;
	char	*value;

	env = ms->envp;
	equal_ptr = ft_strchr(arg, '=');
	if (equal_ptr)
	{
		key = ft_substr(arg, 0, equal_ptr - arg);
		if (!is_valid_key(key))
		{
			print_error_export_arg(key);
			free(key);
			g_exit_status = 1;
			return (0);
		}
		value = ft_strdup(equal_ptr + 1);
		if (!key || !value)
			return (free(key), free(value), -1);
		if (ft_setenv(key, value, &env) != 0)
			return (free(key), free(value), -1);
		free(key);
		free(value);
	}
	else
	{
		key = ft_strdup(arg);
		if (!key)
			return (-1);
		if (!is_valid_key(key))
		{
			print_error_export_arg(key);
			free(key);
			g_exit_status = 1;
			return (0);
		}
		if (ft_setenv(key, NULL, &env) != 0)
			return (free(key), -1);
		free(key);
	}
	return (0);
}

void	builtin_export(t_shell *ms, char **args)
{
	int	i;
	t_envp	*env;
	char	**array;

	env = ms->envp;
	if (!args || !args[1])
	{
		array = ft_envp_lst_to_char_array(ms, true);
		ft_sort_array_of_char(array);
		print_array_of_char(array);
		free_char_array(array);
		g_exit_status = 0;
		return ;
	}
	i = 1;
	while (args && args[i])
	{
		if (process_export_arg(ms, args[i]) != 0)
			print_error_and_exit(ms, "export: memory allocation error", 
				EXIT_FAILURE);
		i++;
	}
	g_exit_status = 0;
}
