/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:39:33 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/04/17 11:28:47 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstsize.c
 * @brief Counts the number of nodes in the list.
 */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*print;
	int		size;

	print = lst;
	size = 0;
	while (print)
	{
		print = print->next;
		size++;
	}
	return (size);
}

/*int	main(void)
{
	t_list	*lst;
	t_list	*ptr;
	t_list	*ptr1;
	int		result;
	
	lst = ft_lstnew((int *)(intptr_t)1);
	ptr = ft_lstnew((int *)(intptr_t)2);
	ptr1 = ft_lstnew((int *)(intptr_t)3);
	lst->next = ptr;
	lst->next->next = ptr1;
	result = ft_lstsize(lst);
	printf("%d\n", result);
	return (0);
}*/