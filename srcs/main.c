#include "../includes/minishell.h"

int	g_signal_number;

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
		tokenizer(&ms);
		expander(&ms);
		if (verify_tokens(&ms) == -1)
			return (ft_printf("token error")); // TODO: ver erro a retornar
		create_cmd_list(&ms);
		ft_token_lstclear(&ms.token);
		execute(&ms);
		ms.token = NULL;
		free(ms.input);
		ft_cmd_lstclear(&ms.command);
	}
	exit_shell(&ms, ms.exit_status);
	return (0);
}
