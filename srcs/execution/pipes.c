#include "minishell.h"

/**
 * @brief counts commands (divided by pipes)
 * 
 * @param ms 
 * @return nr_commands
 */
int count_commands(t_shell *ms)
{
	t_command	*temp;
	int			nr_commands;

	temp = ms->command;
	while (temp)
	{
		nr_commands++;
		temp = temp->next;
	}
	return (nr_commands);
}

// int	create_pipes(t_shell *ms)
// {
// 	int	nr_pipes;
// 	int	i;

// 	nr_pipes = count_commands(ms) - 1;
// 	i = 0;
// 	while (++i < nr_pipes)
// 	{
		
// 	}
// }

int execute(t_shell *ms)
{
	t_command	*temp;

	temp = ms->command;
	while (temp)
	{
		if (temp->is_builtin == 1)
			fill_path(ms);
		temp = temp->next;
	}
	return (0);
}