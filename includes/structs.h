#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_INPUT,
	T_REDIRECT_OUTPUT,
	T_HEREDOC,
	T_REDIR_OUTPUT_APPEND,
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
	int					prev_fd;
	int					heredoc_fd;
	int					is_builtin; //0 para sim, 1 para nao
	char 				**args;
	char				*comm_path;
	t_redir 			*redir; //um comando pode ter mais do que um redirect
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
	int			in_fd;
	int			out_fd;
	int			i; //contador para os comandos
	int			nr_commands;
	t_envp		*envp;
	char		*prompt;
	char		*input;
	t_token		*token;
	t_command 	*command;
	pid_t		*pid;
}	t_shell;

#endif
