/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_lst_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:10:22 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:10:23 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief function to create a new token
 * 
 * @param word
 * @param type
 */
t_token	*ft_token_lstnew(char *word, t_token_type type)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
		return (NULL);
	ptr->word = ft_strdup(word);
	ptr->type = type;
	ptr->quoted = false;
	ptr->ignore_expansion = false;
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
		free((*token)->word);
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}

/**
 * @brief Iterates through the list of tokens and print it.
 */

void	ft_token_lstprint(t_token *lst)
{
	while (lst)
	{
		printf("Token, word: %s type %d\n", lst->word, lst->type);
		lst = lst->next;
	}
}
