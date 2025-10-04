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
            printf("exit\n");
            break;
        }
		if (*ms.input)
			add_history(ms.input);
		if (tokenizer(&ms) != 0)
		{
			free(ms.input);
			ms.input = NULL;
			continue ;
		}
		expander(&ms);
		if (verify_tokens(&ms) == -1)
			return (ft_printf("token error")); // TODO: ver erro a retornar
		create_cmd_list(&ms);
		execute(&ms);
	}
	free_shell(&ms);
	return(g_exit_status);
}
