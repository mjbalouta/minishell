#include "minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd(SHELL_NAME": Not prepared to handle arguments\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	init_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(ms));
	ms->prompt = SHELL_NAME"$ ";
	ms->input = NULL;
	ms->token = NULL;
	ms->exit_status = 0;
	ms->command = NULL;
	init_envp(ms, envp);
	g_signal_number = 0;
}

void	exit_shell(t_shell *ms, int exit_status)
{
	// Free allocated memory before exiting
	free(ms->input);
	ft_envp_lstclear(&ms->envp);
	ft_token_lstclear(&ms->token);
	if (ms->command)
		ft_cmd_lstclear(&ms->command);
	if (ms->pid)
		free(ms->pid);
	exit(exit_status);
}

// TODO: remove this function
void debug_init_shell(t_shell *ms, char **envp)
{
	printf("DEBUG: Shell initialized\n");
	printf("DEBUG: Prompt: %s\n", ms->prompt);
	printf("DEBUG: Exit status: %d\n", ms->exit_status);
	ft_setenv("NULO", NULL, &ms->envp);
	ft_setenv("VAZIO", "", &ms->envp);
	if (ms->envp)
	{
		printf("DEBUG: Environment variables list:\n");
		ft_envp_lstprint(ms->envp);
	}
	else
	{
		printf("DEBUG: No environment variables set.\n");
	}
	printf("DEBUG: Received envp\n");
	print_array_of_char(envp);
	printf("DEBUG: ENV style\n");
	char	**envp2;
	envp2 = ft_envp_lst_to_char_array(ms, false);
	print_array_of_char(envp2);
	free_char_array(envp2);
	printf("DEBUG: ENV export style\n");
	envp2 = ft_envp_lst_to_char_array(ms, true);
	print_array_of_char(envp2);
	free_char_array(envp2);
}
// End of TODO
