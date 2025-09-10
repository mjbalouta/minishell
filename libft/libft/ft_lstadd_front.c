/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:45:09 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:29:08 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstadd_front.c
 * @brief Adds the node ’new’ at the beginning of the list.
 */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

//ver o que falta na main para funcionar corretamente
/*int main(void)
{
    t_list 	*ptr;
    t_list 	*ptr2;
	t_list 	*new;
	t_list	*print;
    ptr = ft_lstnew((void *)(intptr_t)2);
    ptr2 = ft_lstnew((void *)(intptr_t)3);
    ptr->next = ptr2;
	t_list *lst = ptr;
    new = ft_lstnew((void *)(intptr_t)1);
	ft_lstadd_front(&lst, new);
	print = lst;
    while (print)
	{
		printf("%d\n", (int)(intptr_t)print->content);
		print = print -> next;
	}
	free(ptr);
	free(ptr2);
	free(new);
}*/