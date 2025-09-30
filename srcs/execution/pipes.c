#include "minishell.h"

/**
 * @brief main part of the execution of each command
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(int *pipefd, int i, t_shell *ms, int prev_fd)
{
	if (ms->command->redirection)
		define_fds(ms, pipefd, prev_fd);
	if (i == 0)
			dup2(pipefd[1], STDOUT_FILENO);
	else if (i == (ms->nr_commands - 1))
		dup2(prev_fd, STDIN_FILENO);
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	if (prev_fd != -1)
		close (prev_fd);
	if (i < ms->nr_commands - 1)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	// if (comm->is_builtin == 0)
	// 	//funcao para identificar qual o builtin e reencaminhar para a funcao de execucao desse builtin
	// else
	// {
	if (execve(ms->command->comm_path, ms->command->args, ms->full_envp) == -1)
	{
		perror("execve");
		exit(0);
	}
	// }
}

/**
 * @brief executes the commands either on the parent process or forks childs to execute them
 * 
 * @param ms 
 */
void	handle_processes(t_shell *ms)
{
	int	i;
	int	pipefd[2];
	int	id;
	int	prev_fd;

	ms->nr_commands = count_commands(ms);
	i = -1;
	id = 0;
	prev_fd = -1;
	init_pids_container(ms);
	// if (nr_pipes == 0 && ms->command->is_builtin == 0)
	// 	//funcao para identificar builtin
	while (++i < ms->nr_commands)
	{
		if (i < (ms->nr_commands - 1))
        {
            if (pipe(pipefd) != 0)
                exit(1); //create function to exit safely, freeing mem and exiting with exit code
        }
		ms->pid[id] = fork();
		if (ms->pid[id] < 0)
			exit(1);
		if (ms->pid[id++] == 0)
			execute_pipe_cmd(pipefd, i, ms, prev_fd);
		if (i < ms->nr_commands - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		if (ms->command->next)
			ms->command = ms->command->next;
	}
	if (prev_fd != -1)
   		close(prev_fd);
	ms->exit_status = wait_for_child(ms, id);
}

/**
 * @brief main execution function
 * 
 * @param ms 
 */
void	execute(t_shell *ms)
{
	t_command	*temp;

	temp = ms->command;
	init_pids_container(ms);
	while (temp)
	{
		if (temp->is_builtin == 1)
			fill_path(ms, temp);
		temp = temp->next;
	}
	handle_processes(ms);
}
