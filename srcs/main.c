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
		int fd_in = dup(STDIN_FILENO); //guarda os fds base nestas variaveis para sempre que o loop reiniciar os fds darem reset (importante para o heredoc)
		int fd_out = dup(STDOUT_FILENO);
		ms.input = readline(ms.prompt);
        if (!ms.input)
        {
            ft_putendl_fd("exit", 1);
            break;
        }
		if (*ms.input)
			add_history(ms.input);
		if (tokenizer(&ms) != 0 || ms.token == NULL)
		{
			free(ms.input);
			ft_token_lstclear(&ms.token);
			ms.input = NULL;
			continue ;
		}
		expander(&ms);
		if (verify_tokens(&ms) == -1)
			return (ft_printf("syntax error"));
		create_cmd_list(&ms);
		ft_token_lstclear(&ms.token);
		execute(&ms);
		ft_cmd_lstclear(&ms.command);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
	}
	free_shell(&ms);
	return(g_exit_status);
}
