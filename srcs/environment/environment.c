#include "minishell.h"

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
			if (add_envp(envp[i], equal_ptr + 1, &head) != 0)
				exit_shell(ms, EXIT_FAILURE);	// TODO: check correct error
			*equal_ptr = '=';
		}
		i++;
	}
	if (set_minimal_env(&head) != 0)
		exit_shell(ms, EXIT_FAILURE);			// TODO: check correct error
	ms->envp = head;
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
	shlvl = ft_atoi(ft_getenv2("SHLVL", *lst));
	shlvl_ascii = ft_itoa(shlvl + 1);
	if (!shlvl_ascii)
		return (-1);
	ret = ft_setenv("SHLVL", shlvl_ascii, lst);
	free(shlvl_ascii);
	if (ret != 0)
		return (-1);
	return (0);
}

int	add_envp(char *key, char *value, t_envp **lst)
{
	t_envp	*envp;

	envp = ft_envp_lstnew(key, value);
	if (!envp)
		return(-1);
	ft_envp_lstadd_back(lst, envp);
	return (0);
}
