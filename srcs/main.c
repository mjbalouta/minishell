#include "../includes/minishell.h"

int	g_signal_number;

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;
	t_token *tokens;
	t_command *commands;

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
		commands = create_cmd_list(tokens);
		free(ms.input);
	}
	return (ms.exit_status);
}
