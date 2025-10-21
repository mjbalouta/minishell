/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:07:41 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:12:26 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_INPUT,
	T_REDIRECT_OUTPUT,
	T_HEREDOC,
	T_REDIR_OUT_APPEND,
	T_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	bool			quoted;
	bool			ignore_expansion;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_redir				*last_out_redir;
	t_redir				*last_append_redir;
	t_redir				*last_in_redir;
	int					prev_fd;
	int					heredoc_fd;
	int					is_builtin;
	char				**args;
	char				*comm_path;
	t_redir				*redir;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_shell
{
	int			prev_fd;
	int			in_fd;
	int			out_fd;
	int			i;
	int			nr_commands;
	t_envp		*envp;
	char		*prompt;
	char		*input;
	t_token		*token;
	t_cmd		*command;
	pid_t		*pid;
	char		pwd[PATH_MAX];
	char		oldpwd[PATH_MAX];
	bool		ignore_oldpwd;
}	t_shell;

#endif
