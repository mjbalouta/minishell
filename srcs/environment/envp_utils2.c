/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:18 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:19 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putendl_fd(array[i], STDOUT_FILENO);
		i++;
	}
}

void	ft_sort_array_of_char(char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array[i] != NULL)
	{
		j = i + 1;
		while (array[j] != NULL)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
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
