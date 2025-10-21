/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:35 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/21 14:49:19 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			exit_shell(ms, g_exit_status);
		}
		if (*ms->input)
			add_history(ms->input);
		if (tokenizer(ms) != 0 || ms->token == NULL)
		{
			free_shell(ms);
			continue ;
		}
		expander(ms);
		if (execute(ms) == -1)
		{
			free_shell(ms);
			continue ;
		}
		reset_fds(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;

	(void)argv;
	check_args(argc);
	init_shell(&ms, envp);
	shell_loop(&ms);
	return (0);
}
