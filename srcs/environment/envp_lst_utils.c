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

void	ft_envp_lstprint(t_envp *lst)
{
	while (lst)
	{
		if (lst->value)
			printf("DEBUG: %s=%s\n", lst->key, lst->value);
		else
			printf("DEBUG: %s\n", lst->key);
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

char	**ft_envp_lst_to_char_array(t_envp *lst, bool ignore_nulls)
{
	int		n_vars;
	char	**output;
	size_t	i;

	i = 0;
	n_vars = ft_envp_lstsize(lst, ignore_nulls);
	output = ft_calloc(n_vars + 1, sizeof(*output));
	if (!output)
		return (NULL);
	while (lst)
	{
		if (lst->value || !ignore_nulls)
		{
			if (lst->value)
				output[i] = ft_strjoin_three(lst->key, "=", lst->value);
			else
				output[i] = ft_strdup(lst->key);
			if (!output[i])
				return (free_char_array(output), NULL);
			i++;
		}
		lst = lst->next;
	}
	output[i] = NULL;
	return (output);
}
