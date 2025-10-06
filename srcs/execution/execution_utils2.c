#include "minishell.h"

void	verify_comm_path(t_shell *ms)
{
	if (!ms->command->comm_path)
		{
			fprintf(stderr, "%s: command not found\n", ms->command->args[0]); //FAZER UMA CUSTON FPRINTF
			exit_shell(ms, 127);
		}
}