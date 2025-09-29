#include "minishell.h"

/**
 * @brief main part of the execution of each command
 * 
 * @param comm 
 * @param pipefd 
 * @param i 
 * @param ms 
 */
void	execute_pipe_cmd(t_command *comm, int *pipefd, int i, t_shell *ms)
{
	if (comm->redirection)
		define_fds(comm, pipefd);
	if (i == 0)
		comm->prev_fd = pipefd[0];
	dup2(comm->prev_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(comm->prev_fd);
	// if (comm->is_builtin == 0)
	// 	//funcao para identificar qual o builtin e reencaminhar para a funcao de execucao desse builtin
	// else
	// {
	if (execve(comm->comm_path, comm->args, ms->full_envp) == -1)
		exit(0);
	// }
}

/**
 * @brief executes the commands either on the parent process or forks childs to execute them
 * 
 * @param ms 
 */
void	handle_processes(t_shell *ms)
{
	int	nr_pipes;
	int	i;
	int pipefd[2];
	int	id;

	nr_pipes = count_commands(ms) - 1;
	i = -1;
	id = 0;
	init_pids_container(ms);
	// if (nr_pipes == 0 && ms->command->is_builtin == 0)
	// 	//funcao para identificar builtin
	if (nr_pipes == 0 && ms->command->is_builtin == 1) // FUNCIONA SEM REDIRECTS, COM REDIRECTS NÃO, VER COMO FAZER
	{
		ms->pid[id] = fork();
		if (ms->pid[id] < 0)
			exit(1);
		if (ms->pid[id] == 0)
		{
			if (execve(ms->command->comm_path, ms->command->args, ms->full_envp) == -1)
				exit(0);
		}
	}
	else
	{
		while (++i < nr_pipes)
		{
			if (pipe(pipefd) != 0)
				exit(1); //create function to exit safely, freeing mem and exiting with exit code
			ms->pid[id] = fork();
			if (ms->pid[id] < 0)
				exit(1);
			if (ms->pid[id] == 0)
				execute_pipe_cmd(ms->command, pipefd, i, ms);
			ms->command->prev_fd = pipefd[0];
			close(pipefd[1]);
			ms->command = ms->command->next;
			id++;
		}
	}
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
			fill_path(ms);
		temp = temp->next;
	}
	handle_processes(ms);
}
