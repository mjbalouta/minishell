#include "../includes/minishell.h"

int	g_signal_number;

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;

	(void)argv;
	(void)envp;
	check_args(argc);
	init(&ms, envp);
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
		ms.token = tokenizer(&ms);
/* 		if (verify_tokens(&ms) == -1)
			return (1); //ver erro a retornar
		create_cmd_list(&ms);
 */		free(ms.input);
	}
	return (ms.exit_status);
}
