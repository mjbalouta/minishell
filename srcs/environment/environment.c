#include "minishell.h"

static bool	add_envp(char *key, char *value, t_envp **head)
{
	t_envp	*envp;

	envp = ft_envp_lstnew(key, value);
	if (!envp)
	{
		ft_envp_lstclear(head);
		return (false);
	}
	ft_envp_lstadd_back(head, envp);
	return (true);
}

char	**get_envp_without_nulls(t_envp *lst)
{
	int		n_vars;
	char	**output;
	size_t	i;
	size_t	line_size;

	i = 0;
	n_vars = ft_envp_lstsize(lst, true) + 1;
	output = ft_calloc(n_vars, sizeof(*output));
	if (!output)
		return (NULL);
	while (lst)
	{
		if (lst->value)
		{
			line_size = ft_strlen(lst->key) + 1 + ft_strlen(lst->value) + 1;
			output[i] = ft_calloc(line_size, sizeof(char));
			if (!output[i])
				return (NULL);	// TODO: clean array
			ft_strlcat(output[i], lst->key, line_size);
			ft_strlcat(output[i], "=", line_size);
			ft_strlcat(output[i], lst->value, line_size);
			i++;
		}
		output[i] = NULL;
		lst = lst->next;
	}
	return (output);
}

int	set_minimal_env(t_envp **lst)
{
	char	*path;
	int		ret;
	int		shlvl;
	char	*shlvl_ascii;

	path = getcwd(NULL, 0);
	if (!path)
		return (-1);
	ret = ft_setenv("PWD", path, lst);
	free(path);
	if (ret != 0)
		return (-1);
	shlvl = ft_atoi(ft_getenv2("SHLVL", *lst)) + 1;
	shlvl_ascii = ft_itoa(shlvl);
	if (!shlvl_ascii)
		return (-1);
	ret = ft_setenv("SHLVL", shlvl_ascii, lst);
	free(shlvl_ascii);
	if (ret != 0)
		return (-1);
	return (0);
}

void	init_envp(t_shell *ms, char **envp)
{
	int		i;
	t_envp	*head;
	char	*equal_ptr;

	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		equal_ptr = ft_strchr(envp[i], '=');
		if (equal_ptr)
		{
			*equal_ptr = '\0';
			add_envp(envp[i], equal_ptr + 1, &head);
			*equal_ptr = '=';
		}
		i++;
	}
	ms->envp = head;
	set_minimal_env(&head);

 	// print envp
	i = 0;
	while (envp[i] != NULL)
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	
	char	**envp2;
	envp2 = get_envp_without_nulls(head);
	ft_putendl_fd("--------------------------", 1);

	// print envp2
	i = 0;
	while (envp2[i] != NULL)
	{
		ft_putendl_fd(envp2[i], 1);
		i++;
	}

}
