#include "minishell.h"

void	delete_empty_token(t_shell *ms, t_token *to_delete, t_token *previous)
{
	if (to_delete == ms->token)
	{
		ms->token = to_delete->next;
	}
	else if (previous)
	{
		previous->next = to_delete->next;
	}
	free(to_delete->word);
	free(to_delete);
}

bool	is_heredoc_token(t_token *token)
{
	return (token && token->type == T_HEREDOC);
}
