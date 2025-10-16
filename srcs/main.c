#include "../includes/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	process_tokens(t_shell *ms)
{
	int		result;

	if (tokenizer(ms) != 0 || ms->token == NULL)
    {
            free_shell(ms);
            close_both_fds(ms->in_fd, ms->out_fd);
            return (-1);
    }
	expander(ms);
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

int main(int argc, char **argv, char **envp)
{
    t_shell ms;
    (void)argv;
    check_args(argc);
    init_shell(&ms, envp);
    while (true)
    {
        ms.in_fd = dup(STDIN_FILENO);
        ms.out_fd = dup(STDOUT_FILENO);
        ms.input = readline(ms.prompt);
        if (!ms.input)
        {
            ft_putendl_fd("exit", 1);
            close_both_fds(ms.in_fd, ms.out_fd);
            break ;
        }
        if (*ms.input)
            add_history(ms.input);
        // if (tokenizer(&ms) != 0 || ms.token == NULL)
        // {
        //     free(ms.input);
        //     ft_token_lstclear(&ms.token);
        //     ms.input = NULL;
        //     close_both_fds(ms.in_fd, ms.out_fd);
        //     continue ;
        // }
        if (process_tokens(&ms) == -1)
            continue ;
        create_cmd_list(&ms);
        execute(&ms);
        ft_cmd_lstclear(&ms.command);
        ft_token_lstclear(&ms.token);
        dup2(ms.in_fd, STDIN_FILENO);
        dup2(ms.out_fd, STDOUT_FILENO);
        close_both_fds(ms.in_fd, ms.out_fd);
    }
    ft_envp_lstclear(&ms.envp);
    free_shell(&ms);
    return(g_exit_status);
}
