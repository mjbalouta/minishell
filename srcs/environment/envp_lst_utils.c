#include "minishell.h"

t_envp	*ft_envp_lstnew(char *key, char *value)
{
	t_envp	*ptr;

	ptr = malloc(sizeof(t_envp));
	if (!ptr)
		return (NULL);
	ptr->key = ft_strdup(key);
	if (value)
		ptr->value = ft_strdup(value);
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

void	ft_envp_lstprint(t_envp *lst)
{
	while (lst)
	{
		printf("Envp, key: %s value %s\n", lst->key, lst->value);
		lst = lst->next;
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
