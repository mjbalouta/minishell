#include "minishell.h"

char	*ft_getenv(const char *key, t_envp *lst)
{
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

/* int	ft_setenv(const char *key, const char *value, int flag, t_envp **lst)
{
	t_envp	*head;
	
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}
 */