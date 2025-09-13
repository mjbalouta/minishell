#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_INPUT,
	T_REDIRECT_OUTPUT,
	T_HEREDOC,
	T_REDIRECT_OUTPUT_APPEND,
	T_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	**envp;
	char	*prompt;
	char	*input;
	t_token	*token;
	int		exit_status;
}	t_shell;

#endif
