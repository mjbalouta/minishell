#include "minishell.h"

t_token	*ft_token_lstnew(char *word, t_token_type type)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
		return (NULL);
	ptr->word = word;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

void	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
}

/**
 * @brief function that frees the token linked list
 * 
 * @param token 
 */
void	ft_token_lstclear(t_token **token)
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

/**
 * @brief Iterates through the list of tokens and print it.
 */

void	ft_token_lstprint(t_token *lst)
{
	while (lst)
	{
		printf("Token, word: %s type %d\n", lst->word, lst->type);
		lst = lst -> next;
	}
}
