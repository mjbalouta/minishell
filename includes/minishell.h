#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./libft-projects/get-next-line/get_next_line.h"
# include "./libft-projects/libft/libft.h"
# include "./libft-projects/printf/libftprintf.h"

enum e_token_type
{
	T_WORD,
	T_REDIRECT_INPUT,
	T_REDIRECT_OUTPUT,
	T_HEREDOC,
	T_REDIRECT_OUTPUT_APPEND,
	T_PIPE
};

typedef struct s_token
{
	char			*word;
	e_token_type	type;
	struct s_token	*next;
}	t_token;

#endif
