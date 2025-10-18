#include "minishell.h"

void	print_error_export_arg(char *arg);
void	print_export_envp(t_shell *ms);
bool	is_valid_key_char(char c, int pos);

/**
 * @brief checks the key of a environment variable
 * 
 * return	0 - valid key
 * 			1 - valid key, concatenation
 * 			-1 - invalid key
 * 
 * @param key key to check
 * @return int
 */
static int	check_key(char *key)
{
	size_t	i;
	size_t	len;
	int		is_concat;

	is_concat = 0;
	if (!key || !*key)
		return (-1);
	len = ft_strlen(key);
	if (len > 0 && key[len - 1] == '+')
	{
		len--;
		is_concat = 1;
	}
	i = 0;
	while (i < len)
	{
		if (!is_valid_key_char(key[i], i))
			return (-1);
		i++;
	}
	return (is_concat);
}

static int	process_export_arg_w_equal(t_shell *ms, char *arg, char *equal_ptr)
{
	t_envp	*env;
	char	*key;
	char	*value;

	env = ms->envp;
	key = ft_substr(arg, 0, equal_ptr - arg);
	if (check_key(key) == -1)
	{
		print_error_export_arg(key);
		free(key);
		g_exit_status = 1;
		return (0);
	}
	value = ft_strdup(equal_ptr + 1);
	if (!key || !value)
		return (free(key), free(value), -1);
	if (check_key(key) == 0)
		if (ft_setenv(key, value, false, &env) != 0)
			return (free(key), free(value), -1);
	if (check_key(key) == 1)
		if (ft_setenv(key, value, true, &env) != 0)
			return (free(key), free(value), -1);
	free(key);
	free(value);
	return (0);
}

static int	process_export_arg_no_equal(t_shell *ms, char *arg)
{
	t_envp	*env;
	char	*key;

	env = ms->envp;
	key = ft_strdup(arg);
	if (!key)
		return (-1);
	if (check_key(key) != 0)
	{
		print_error_export_arg(key);
		free(key);
		g_exit_status = 1;
		return (0);
	}
	if (ft_setenv(key, NULL, false, &env) != 0)
		return (free(key), -1);
	free(key);
	return (0);
}

static int	process_export_arg(t_shell *ms, char *arg)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(arg, '=');
	if (equal_ptr)
		return (process_export_arg_w_equal(ms, arg, equal_ptr));
	else
		return (process_export_arg_no_equal(ms, arg));
	return (0);
}

void	builtin_export(t_shell *ms, t_cmd *cmd)
{
	int		i;

	g_exit_status = 0;
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-", 1) == 0)
		{
			print_error("export: options aren't supported");
			g_exit_status = 2;
			return ;
		}
		i++;
	}
	if (!cmd->args || !cmd->args[1])
		return (print_export_envp(ms));
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (process_export_arg(ms, cmd->args[i]) != 0)
			print_error_and_exit(ms, "export: memory allocation error",
				EXIT_FAILURE);
		i++;
	}
}
