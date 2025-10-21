/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:15 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:16 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_setenv_helper(t_envp *env_node, bool concat, char *value)
{
	char	*new_value;
	char	*temp;

	if (value)
	{
		if (env_node->value && concat)
		{
			temp = ft_strjoin(env_node->value, value);
			if (!temp)
				return (-1);
			free(env_node->value);
			env_node->value = temp;
		}
		else
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (-1);
			free(env_node->value);
			env_node->value = new_value;
		}
	}
	return (EXIT_SUCCESS);
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
int	ft_setenv(char *key, char *value, bool concat, t_envp **lst)
{
	t_envp	*env_node;

	if (concat)
		key[ft_strlen(key) - 1] = '\0';
	env_node = ft_checkenv(key, *lst);
	if (!env_node)
		return (add_envp(key, value, lst));
	else
		return (ft_setenv_helper(env_node, concat, value));
}

/**
 * @brief deletes an environment variable
 * 
 * Returns 0 on success, or -1 on error.
 * If the key does not exist, the function does nothing and returns 0.
 * 
 * @param key key to delete
 * @param lst environment list
 * @return int
 */
int	ft_unsetenv(char *key, t_envp **head)
{
	t_envp	*temp;
	t_envp	*prev;

	temp = *head;
	if (temp != NULL && ft_strcmp(key, temp->key) == 0)
	{
		*head = temp->next;
		free_key_value(temp->key, temp->value);
		free(temp);
		temp = NULL;
		return (EXIT_SUCCESS);
	}
	while (temp != NULL && ft_strcmp(key, temp->key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (EXIT_SUCCESS);
	prev->next = temp->next;
	free_key_value(temp->key, temp->value);
	free(temp);
	temp = NULL;
	return (EXIT_SUCCESS);
}
