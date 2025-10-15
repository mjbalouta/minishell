#include "minishell.h"

/**
 * @brief verifies if the command->arg[0] is already a path.
 * 
 * @param ms 
 * @return 1 -> is a path; 0 -> is not a path.
 */
int	is_path(t_cmd *command)
{
	int	i;

	i = 0;
	if (!command->args[0])
		return (0);
	while (command->args[0][i])
	{
		if (command->args[0][i] == '/')
		{
			command->comm_path = ft_strdup(command->args[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief creates the path of the command which will be tested
 * with the function access() to check if it's executable.
 * 
 * @param path (the current path in which it is searching for the command)
 * @param command 
 * @return char* test_path
 */
char	*create_test_path(char *path, char *command)
{
	char	*test_path;
	char	*path_slash;

	path_slash = ft_strjoin(path, "/");
	test_path = ft_strjoin(path_slash, command);
	free(path_slash);
	return (test_path);
}

/**
 * @brief fills the command->comm_path of the command struct (needed for execve)
 * 
 * @param ms 
 */
void	fill_path(t_shell *ms, t_cmd *command)
{
	char	*path_full_str;
	char	**path_list;
	char	*test_path;
	int		i;

	if (is_path(command) || (command->args[0] && !command->args[0][0]))
		return ;
	path_full_str = ft_getenv("PATH", ms->envp);
	if (!path_full_str)
		return ;
	path_list = ft_split(path_full_str, ':');
	i = -1;
	while (path_list[++i])
	{
		test_path = create_test_path(path_list[i], command->args[0]);
		if (access(test_path, X_OK) == 0)
		{
			command->comm_path = test_path;
			free_char_array(path_list);
			return ;
		}
		free(test_path);
	}
	free_char_array(path_list);
}
