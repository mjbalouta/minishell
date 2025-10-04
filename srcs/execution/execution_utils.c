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

void	write_inside_pipe(int *heredoc_fd, char *line)
{
	write(heredoc_fd[1], line, ft_strlen(line));
	write(heredoc_fd[1], "\n", 1);
}

void	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}
