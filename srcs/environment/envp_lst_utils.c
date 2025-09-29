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

/**
 * @brief Converts the environment variable linked list to a char array
 * 
 * @param ms Pointer to the shell structure containing the envp list.
 * @param export_style If true, formats output for export; otherwise, standard key=value.
 * @return A newly allocated NULL-terminated array of strings representing environment variables.
 */
char	**ft_envp_lst_to_char_array(t_shell *ms, bool export_style)
{
	int		n_vars;
	char	**output;
	size_t	i;
	t_envp *lst;

	i = 0;
	lst = ms->envp;
	n_vars = ft_envp_lstsize(lst, !export_style);
	output = ft_calloc(n_vars + 1, sizeof(*output));
	if (!output)
		exit_shell(ms, EXIT_FAILURE); // TODO: check correct error
	while (lst)
	{
		if (lst->value || export_style)
		{
			if (lst->value)
				if (export_style)
					output[i] = ft_strjoin_five("declare -x ", lst->key, "=\"", lst->value, "\"");
				else
					output[i] = ft_strjoin_three(lst->key, "=", lst->value);
			else
				if (export_style)
					output[i] = ft_strjoin("declare -x ", lst->key);
				else
					output[i] = ft_strdup(lst->key);
			if (!output[i])
			{
				free_char_array(output);
				exit_shell(ms, EXIT_FAILURE); // TODO: check correct error
			}
			i++;
		}
		lst = lst->next;
	}
	output[i] = NULL;
	return (output);
}
