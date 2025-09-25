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
	struct s_token	*next;
}	t_token;

//estrutura para guardar o tipo de redirect e o respetivo nome do ficheiro
typedef struct s_redir
{
    t_token_type	type;   // <, >, >>, << 
    char 			*filename;
    struct s_redir	*next;
}	t_redir;

//estrutura para guardar cada comando entre pipes
typedef struct s_command
{
	int					is_builtin; //0 para sim, 1 para nao
	char 				**args;
	char				*comm_path;
	t_redir 			*redirection; //um comando pode ter mais do que um redirect
	struct s_command 	*next;
}	t_command;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_shell
{
	t_envp		*envp;
	char		*prompt;
	char		*input;
	t_token		*token;
	t_command 	*command;
	int			exit_status;
}	t_shell;

#endif
