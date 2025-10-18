#include "minishell.h"

void	print_error_export_arg(char *arg)
{
	ft_putstr_fd(SHELL_NAME": export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_export_envp(t_shell *ms)
{
	char	**array;

	array = ft_envp_lst_to_char_array(ms, true);
	ft_sort_array_of_char(array);
	print_array_of_char(array);
	free_char_array(array);
	g_exit_status = 0;
}

bool	is_valid_key_char(char c, int pos)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	if (pos > 0 && (c >= '0' && c <= '9'))
		return (true);
	return (false);
}
