/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:53:01 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:27:15 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Takes a node as parameter and frees its content
using the function ’del’. Free the node itself but
does NOT free the next node.
 */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}
/*int	main(void)
{
	t_list	*lst;
	t_list	*ptr;
	t_list	*ptr1;
	t_list	*head;

	// Dynamically allocate memory for the integer values
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	int *c = malloc(sizeof(int));
	*a = 1;
	*b = 2;
	*c = 3;

	// Create the list nodes, each node holds a pointer to an integer
	ptr = ft_lstnew(a); // node 1
	lst = ft_lstnew(b);  // node 2
	ptr1 = ft_lstnew(c); // node 3
	head = ptr;
	ptr->next = lst;
	lst->next = ptr1;
	ptr->next = lst->next; // skip lst
	ft_lstdelone(lst, free);
	ptr->next = ptr1;
	ptr = head;
	while (ptr)
	{
		printf("%d\n", *(int *)ptr->content);
		ptr = ptr->next;
	}
	free(ptr1->content);
	free(ptr1);
	free(head->content);
	free(head);
	return (0);
}*/