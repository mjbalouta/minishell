#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "minishell"

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "structs.h"
# include "../libft/get-next-line/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/libftprintf.h"

// Global variable
extern int	g_signal_number;

void	check_args(int argc);
void	init(t_shell *ms, char **envp);
int		is_redir(t_token *token);
int		count_args(t_shell *ms);
void	create_cmd_list(t_shell *ms);
int		verify_tokens(t_shell *ms);
void	verify_if_bultin(t_shell *ms);

t_token *tokenizer(t_shell *ms);
bool	ft_isquote(int c);
bool	ft_isseparator(int c);
bool	find_matching_quote(char quote,char *input, size_t *i);

t_token	*ft_token_lstnew(char *word, t_token_type type);
void	ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **token);
void	ft_token_lstprint(t_token *lst);

void	init_envp(t_shell *ms, char **envp);
t_envp	*ft_envp_lstnew(char *key, char *value);
void	ft_envp_lstadd_back(t_envp **lst, t_envp *new);
void	ft_envp_lstclear(t_envp **envp);
void	ft_envp_lstprint(t_envp *lst);
int		ft_envp_lstsize(t_envp *lst, bool ignore_nulls);
char	*ft_getenv(const char *varname, t_envp *lst);

int		is_path(t_shell *ms);
char	*create_test_path(char *path, char *command);
void	fill_path(t_shell *ms, t_command *command);
int		count_commands(t_shell *ms);
int		create_pipes(t_shell *ms);
void	init_pids_container(t_shell *ms);
int		wait_for_child(t_shell *ms, int cmd_count);
void	define_fds(t_shell *ms, int *pipefd, int prev_fd);
void	execute_pipe_cmd(int *pipefd, int i, t_shell *ms, int prev_fd);
void	handle_processes(t_shell *ms);
void	execute(t_shell *ms);



#endif
