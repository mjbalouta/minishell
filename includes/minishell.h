#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "minishell"

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "../libft/get-next-line/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/libftprintf.h"

// Global variable
extern int	g_signal_number;

void	check_args(int argc);
void	init(t_shell *ms, char **envp);

#endif
