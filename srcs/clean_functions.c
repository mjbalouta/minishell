#include "minishell.h"

/**
 * @brief function that frees the token linked list
 * 
 * @param token 
 */
void	clear_token_lst(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		free((*token)->word);
		free(*token);
		*token = temp;
	}
	*token = NULL;
}