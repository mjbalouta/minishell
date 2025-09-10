/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:49:50 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:26:02 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstiter.c
 * @brief Iterates through the list ’lst’ and applies the
function ’f’ to the content of each node.
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst -> next;
	}
}

/* void	ft_plusone(void *content)
{
	int *num = (int *)content;
	(*num)++;
}

int	main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;

	t_list *n1 = ft_lstnew(&a);
	t_list *n2 = ft_lstnew(&b);
	t_list *n3 = ft_lstnew(&c);

	n1->next = n2;
	n2->next = n3;

	printf("Before:\n");
	t_list *tmp = n1;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}

	ft_lstiter(n1, ft_plusone);

	printf("\nAfter:\n");
	tmp = n1;
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}
	free(n1);
	free(n2);
	free(n3);
	return (0);
}  */