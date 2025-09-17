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
int		is_redir(t_token *token);
int		count_args(t_shell *ms);
void	create_cmd_list(t_shell *ms);

t_token *tokenizer(t_shell *ms);
bool	ft_isquote(int c);
bool	ft_isseparator(int c);
bool	find_matching_quote(char quote,char *input, size_t *i);

t_token	*ft_token_lstnew(char *word, t_token_type type);
void	ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **token);
void	ft_token_lstprint(t_token *lst);

#endif
