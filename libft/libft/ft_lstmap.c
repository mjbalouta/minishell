/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:46:51 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 12:13:58 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstmap.c
 * @brief Iterates through the list ’lst’, applies the
function ’f’ to each node’s content, and creates
a new list resulting of the successive applications
of the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_node;
	t_list	*last_node;
	t_list	*set;

	new = NULL;
	last_node = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = ft_lstnew(set);
		if (!new_node)
		{
			del(set);
			return (ft_lstclear(&new, del), NULL);
		}
		if (!new)
			new = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		lst = lst ->next;
	}
	return (new);
}

/*void *ft_plusone(void *content)
{
	int *num = malloc(sizeof(int));
	if (!num)
		return (NULL);
	*num = (*(int *)content) + 1;
	return num;
}

int main(void)
{
	int a = 1, b = 2, c = 3;

	t_list *n1 = ft_lstnew(&a);
	t_list *n2 = ft_lstnew(&b);
	t_list *n3 = ft_lstnew(&c);
	n1->next = n2;
	n2->next = n3;
	t_list *tmp = n1;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}

	t_list *new_list = ft_lstmap(n1, ft_plusone, free);

	printf("\n\n");
	tmp = new_list;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}

	printf("\nOriginal List Unchanged\n");
	tmp = n1;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}

	ft_lstclear(&new_list, free);
	free(n1);
	free(n2);
	free(n3);
	return 0;
}*/
