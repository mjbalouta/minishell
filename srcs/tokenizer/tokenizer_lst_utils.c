#include "minishell.h"

t_token	*ft_lstnew_token(char *word, t_token_type type)
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

void	ft_lstadd_back_token(t_token **lst, t_token *new)
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

void	ft_lstclear_token(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

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
