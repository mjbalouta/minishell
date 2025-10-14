#include "../includes/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;

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
			close(ms.in_fd);
			close(ms.out_fd);
            break ;
        }
		if (*ms.input)
			add_history(ms.input);
		if (tokenizer(&ms) != 0 || ms.token == NULL)
		{
			free(ms.input);
			ft_token_lstclear(&ms.token);
			ms.input = NULL;
			close(ms.in_fd);
			close(ms.out_fd);
			continue ;
		}
		expander(&ms);
		if (verify_tokens(&ms) == -1)
		{
			close(ms.in_fd);
			close(ms.out_fd);
			print_error_and_exit(&ms, "syntax error", 2);
		}
		create_cmd_list(&ms);
		execute(&ms);
		ft_cmd_lstclear(&ms.command);
		ft_token_lstclear(&ms.token);
		dup2(ms.in_fd, STDIN_FILENO);
		dup2(ms.out_fd, STDOUT_FILENO);
		close(ms.in_fd);
		close(ms.out_fd);
	}
	free_shell(&ms);
	return(g_exit_status);
}
