// TODO: File to delete, delete also the include in the header file

#include "minishell.h"

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
