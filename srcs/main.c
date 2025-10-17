#include "../includes/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

void	shell_loop(t_shell *ms)
{
	while (true)
    {
        ms->in_fd = dup(STDIN_FILENO);
        ms->out_fd = dup(STDOUT_FILENO);
        ms->input = readline(ms->prompt);
        if (!ms->input)
        {
            ft_putendl_fd("exit", 1);
            close_both_fds(ms->in_fd, ms->out_fd);
            exit_shell(ms, g_exit_status);
        }
        if (*ms->input)
            add_history(ms->input);
        if (tokenizer(ms) != 0 || ms->token == NULL)
        {
            free(ms->input);
            ft_token_lstclear(&ms->token);
            ms->input = NULL;
            close_both_fds(ms->in_fd, ms->out_fd);
            continue ;
        }
		expander(ms);
        if (execute(ms) == -1)
            continue ;
        reset_fds(ms);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_shell ms;
    (void)argv;
    check_args(argc);
    init_shell(&ms, envp);
    shell_loop(&ms);
	return (0);
}
