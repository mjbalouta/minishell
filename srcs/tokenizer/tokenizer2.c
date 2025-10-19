#include "minishell.h"

void	insert_expanded_tokens(t_shell *ms, t_token *current, char *tmp)
{
	char	**words;
	t_token	*new_token;
	size_t	i;
	t_token *new_lst;
	t_token *last_token;
	
	(void)ms;
	new_lst = NULL;
	words = ft_split(tmp, ' ');
	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		new_token = ft_token_lstnew(words[i], T_WORD);
		if (!new_token)
		{
			free_char_array(words);
			return ;
		}
		ft_token_lstadd_back(&new_lst, new_token);
		last_token = new_token;
		i++;
	}
	free_char_array(words);
	last_token->next = current->next;
	current->next = new_lst;
	current->word[0] = '\0';
}
