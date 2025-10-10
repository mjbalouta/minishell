#include "../includes/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;
	int		fd_in;
	int		fd_out;

	(void)argv;
	check_args(argc);
	init_shell(&ms, envp);
	while (true)
	{
		fd_in = dup(STDIN_FILENO); //guarda os fds base nestas variaveis para sempre que o loop reiniciar os fds darem reset (importante para o heredoc)
		fd_out = dup(STDOUT_FILENO);
		ms.input = readline(ms.prompt);
        if (!ms.input)
        {
            ft_putendl_fd("exit", 1);
            break ;
        }
		if (*ms.input)
			add_history(ms.input);
		if (tokenizer(&ms) != 0 || ms.token == NULL)
		{
			free(ms.input);
			ft_token_lstclear(&ms.token);
			ms.input = NULL;
			close(fd_in);
			close(fd_out);
			continue ;
		}
		expander(&ms);
		if (verify_tokens(&ms) == -1)
			return (ft_printf("syntax error"));
		create_cmd_list(&ms);
		execute(&ms);
		ft_cmd_lstclear(&ms.command);
		ft_token_lstclear(&ms.token);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
	}
	close(fd_in);
	close(fd_out);
	free_shell(&ms);
	return(g_exit_status);
}
