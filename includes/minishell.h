#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# define SHELL_NAME "minishell"

#ifndef ECHOCTL
# define ECHOCTL 0001000
#endif

#if defined (READLINE_LIBRARY)
#  include "posixstat.h"
#  include "readline.h"
#  include "history.h"
#else
#  include <sys/stat.h>
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

# include <stdio.h>
# include <stdbool.h>
# include <termios.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <stdlib.h>

# include "structs.h"
# include "../libft/get-next-line/get_next_line.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/libftprintf.h"

// Global variable
extern volatile sig_atomic_t	g_exit_status;

// TODO: remove this prototype
void	ft_envp_lstprint(t_envp *lst);
// TODO

void	check_args(int argc);
void	init_shell(t_shell *ms, char **envp);
void	free_shell(t_shell *ms);
void	exit_shell(t_shell *ms, int exit_status);
void	debug_init_shell(t_shell *ms, char **envp);
void	print_error_and_exit(t_shell *ms, char *message, int exit_status);
void	print_error(char *message);

void	init_signals();

int		is_redir(t_token *token);
int		count_args(t_shell *ms);
void	create_cmd_list(t_shell *ms);
int		verify_tokens(t_shell *ms);
void	verify_if_bultin(t_shell *ms);
void	ft_cmd_lstclear(t_command **lst);
void	free_redirection_list(t_redir *redir);

int		tokenizer(t_shell *ms);
bool	ft_isquote(int c);
bool	ft_isseparator(int c);
bool	find_matching_quote(char quote,char *input, size_t *i);
t_token	*ft_token_lstnew(char *word, t_token_type type);
void	ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **token);
void	ft_token_lstprint(t_token *lst);

int		init_envp(t_shell *ms, char **envp);
int		set_minimal_env(t_envp **lst);
int		add_envp(char *key, char *value, t_envp **lst);
t_envp	*ft_envp_lstnew(char *key, char *value);
void	ft_envp_lstadd_back(t_envp **lst, t_envp *new);
void	ft_envp_lstclear(t_envp **envp);
int		ft_envp_lstsize(t_envp *lst, bool ignore_nulls);
char	**ft_envp_lst_to_char_array(t_shell *ms, bool export_style);
char	*ft_getenv(const char *varname, t_envp *lst);
char	*ft_getenv2(const char *key, t_envp *lst);
t_envp	*ft_checkenv(char *key, t_envp *lst);
int		ft_setenv(char *key, char *value, t_envp **lst);
int		ft_unsetenv(char *key, t_envp **lst);
void	free_char_array(char **array);
void	print_array_of_char(char **array);

void	expander(t_shell *ms);
char	*expand_word(char *word, t_shell *ms);
char	*expand_tilde(char *str, t_envp *env);

int		is_path(t_command *command);
char	*create_test_path(char *path, char *command);
void	fill_path(t_shell *ms, t_command *command);
int		count_commands(t_shell *ms);
int		create_pipes(t_shell *ms);
void	init_pids_container(t_shell *ms);
int		wait_for_child(t_shell *ms, int cmd_count);
void	define_fds(t_shell *ms, int *pipefd, int prev_fd, int i);
void	handle_without_redir(int i, int *pipefd, int prev_fd, t_shell *ms);
void	handle_output_redir(int prev_fd, t_shell *ms, int out_fd, int i);
void	handle_input_redir(int prev_fd, t_shell *ms, int *pipefd, int i);
void	execute_pipe_cmd(int *pipefd, int i, t_shell *ms, int prev_fd);
void	handle_processes(t_shell *ms);
void	execute(t_shell *ms);
void	close_pipes(int *pipefd);
void	write_inside_pipe(int *heredoc_fd, char *line);
void	ft_env(t_shell *ms, char **args);
void	ft_exit(t_shell *ms, char **args);
void	verify_comm_path(t_shell *ms);

void	select_builtin(t_shell *ms);

#endif
