#include "minishell.h"

void	init_pids_container(t_shell *ms)
{
	int	nr_cmds;

	nr_cmds = count_commands(ms);
	ms->pid = malloc(sizeof(pid_t) * nr_cmds);
	if (!ms->pid)
		return ;
}

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
	nr_commands = 0;
	while (temp)
	{
		nr_commands++;
		temp = temp->next;
	}
	return (nr_commands);
}
/**
 * @brief waits for every process id (pid) to end
 * 
 * @param ms 
 * @param cmd_count 
 * @return status of the last process id to return to the main function
 */
int	wait_for_child(t_shell *ms, int cmd_count)
{
	int	last_status;
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(ms->pid[i], &status, 0);
		last_status = status;
		i++;
	}
	return (last_status >> 8);
}

/**
 * @brief define both ends of the pipe (used when there are redirections in the commands): when there's a <,
 * the read part of the pipe should be the fd of the file, when > it's the write side of the pipe that changes
 * 
 * @param comm 
 * @param pipefd 
 */
void	define_fds(t_shell *ms, int *pipefd)
{
	if (ms->command->redirection->type == T_REDIRECT_INPUT)
		pipefd[0] = open(ms->command->redirection->filename, O_RDONLY);
	else if (ms->command->redirection->type == T_REDIRECT_OUTPUT)
		pipefd[1] = open(ms->command->redirection->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipefd[0] < 0 || pipefd[1] < 0)
	{
		perror(ms->command->redirection->filename);
		exit(1);
	}
}
