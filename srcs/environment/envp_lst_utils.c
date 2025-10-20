/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:09 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:11 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_envp_lstnew(char *key, char *value)
{
	t_envp	*ptr;

	ptr = malloc(sizeof(t_envp));
	if (!ptr)
		return (NULL);
	ptr->key = ft_strdup(key);
	if (!ptr->key)
		return (free(ptr), NULL);
	if (value)
	{
		ptr->value = ft_strdup(value);
		if (!ptr->value)
			return (free(ptr->key), free(ptr), NULL);
	}
	else
		ptr->value = NULL;
	ptr->next = NULL;
	return (ptr);
}

void	ft_envp_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*ptr;

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

void	ft_envp_lstclear(t_envp **lst)
{
	t_envp	*temp;

	while (*lst)
	{
		free((*lst)->key);
		free((*lst)->value);
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

int	ft_envp_lstsize(t_envp *lst, bool ignore_nulls)
{
	int	size;

	size = 0;
	while (lst)
	{
		if (lst->value)
			size++;
		else
			if (!ignore_nulls)
				size++;
		lst = lst->next;
	}
	return (size);
}
