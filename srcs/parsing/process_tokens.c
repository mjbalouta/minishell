#include "minishell.h"

/**
 * @brief Checks tokens syntax (calls verify tokens)
 * 
 * @param ms 
 * @return int 
 */
int	check_syntax(t_shell *ms)
{
	int		result;

	result = verify_tokens(ms);
	if (result != 0)
	{
		if (result == -1)
		{
			ft_putstr_fd("syntax error\n", STDERR_FILENO);
			g_exit_status = 2;
		}
		else if (result == 2)
			g_exit_status = 0;
		free_shell(ms);
		close_both_fds(ms->in_fd, ms->out_fd);
		return (-1);
	}
	return (0);
}
/**
 * @brief Checks syntax and calls function to create command list
 * 
 * @param ms 
 * @return int 
 */
int	process_tokens(t_shell *ms)
{
	if (check_syntax(ms) == -1)
	 	return (-1);
	create_cmd_list(ms);
	return (0);
}