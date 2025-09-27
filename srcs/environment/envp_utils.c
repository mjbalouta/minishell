#include "minishell.h"

/**
 * @brief get an environment variable
 * 
 * returns NULL if the variable does not exists
 * 
 * @param key key to search
 * @param lst environment list
 * @return char*
 */
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

/**
 * @brief get an environment variable
 * 
 * returns a empty string if the variable does not exists
 * 
 * @param key key to search
 * @param lst environment list
 * @return char*
 */
char	*ft_getenv2(const char *key, t_envp *lst)
{
	char	*result;

	result = ft_getenv(key, lst);
	if (!result)
		return ("");
	else
		return (result);
}

/**
 * @brief check an environment variable
 * 
 * returns a pointer to the t_envp struct if the variable exists and 
 * NULL if it does not
 * 
 * @param key key to search
 * @param lst environment list
 * @return t_envp*
 */
t_envp	*ft_checkenv(char *key, t_envp *lst)
{
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/**
 * @brief change or add an environment variable
 * 
 * return 0 on success, or -1 on error
 * 
 * @param key key to search
 * @param value key to search
 * @param lst environment list
 * @return int
 */
int	ft_setenv(char *key, char *value, t_envp **lst)
{
	t_envp	*env_node;
	
	env_node = ft_checkenv(key, *lst);

	if (!env_node)
	{
		env_node = ft_envp_lstnew(key, value);
		if (!env_node)
			return (-1);
		ft_envp_lstadd_back(lst, env_node);
	}
	else
	{
		env_node->value = ft_strdup(value);
		if (!env_node->value)
			return (-1);
	}
	return (0);
}

/**
 * @brief deletes an environment variable
 * 
 * return 0 on success, or -1 on error
 * 
 * @param key key to delete
 * @param lst environment list
 * @return int
 */
int	ft_unsetenv(char *key, t_envp **lst)
{
    t_envp *temp = *lst;
	t_envp *prev;

    if (temp != NULL && ft_strcmp(key, temp->key) == 0)
	{
        *lst = temp->next;
        free(temp);
        return (0);
    }
    while (temp != NULL && ft_strcmp(key, temp->key) != 0)
	{
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return (0);
    prev->next = temp->next;
    free(temp);
	return (0);
}

void	free_char_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_array_of_char(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putendl_fd(array[i], 1);
		i++;
	}	
}
