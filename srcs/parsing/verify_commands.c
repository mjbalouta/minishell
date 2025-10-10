#include "minishell.h"

/**
 * @brief fills a flag if the command is a built-in (flag 0 for yes,
 * flag 1 for no)
 * 
 * @param ms 
 */
void	verify_if_bultin(t_command *cmd)
{
	if (cmd->args[0] && ((ft_strcmp(cmd->args[0], "echo") == 0)
	|| (ft_strcmp(cmd->args[0], "cd") == 0)
	|| (ft_strcmp(cmd->args[0], "pwd") == 0)
	|| (ft_strcmp(cmd->args[0], "export") == 0)
	|| (ft_strcmp(cmd->args[0], "unset") == 0)
	|| (ft_strcmp(cmd->args[0], "env") == 0)
	|| (ft_strcmp(cmd->args[0], "exit") == 0)))
	{
		cmd->is_builtin = 0;
	}
	else
		cmd->is_builtin = 1;
}
