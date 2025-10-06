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
		ms.input = readline(ms.prompt);
        if (!ms.input)
        {
            ft_putendl_fd("exit", 1);
            break;
        }
		//IMPORTANTE: se o input apenas contiver whitespace, não fazemos nada e mostramos novamente o prompt (não adicionar estes ao history)
		if (*ms.input)
			add_history(ms.input);
		if (tokenizer(&ms) != 0)
		{
			free(ms.input);
			ft_token_lstclear(&ms.token);
			ms.input = NULL;
			continue ;
		}
		expander(&ms);
		if (verify_tokens(&ms) == -1)
			return (ft_printf("token error")); // TODO: ver erro a retornar
		create_cmd_list(&ms);
		ft_token_lstclear(&ms.token);
		execute(&ms);
		ft_cmd_lstclear(&ms.command);
	}
	free_shell(&ms);
	return(g_exit_status);
}
