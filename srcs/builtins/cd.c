#include "minishell.h"

/* static char	*get_cd_target(t_shell *ms, char **args, int *print_path)
{
	char	*path;

	*print_path = 0;
	if (!args[1] || !args[1][0])
	{
		path = ft_getenv("HOME", ms->envp);
		if (!path)
			print_error("cd: HOME not set\n");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_getenv("OLDPWD", ms->envp);
		if (!path)
			print_error("cd: OLDPWD not set\n");
		else
			*print_path = 1;
	}
	else
		path = args[1];
	return (path);
}

static void	print_error_cd(char *arg)
{
	ft_putstr_fd(SHELL_NAME": cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
*/
void	builtin_cd(t_shell *ms, t_command *cmd)
{
/* 	char	*path;
 *//* 	int		print_path;
 */
	(void)ms;
	if (cmd->args && cmd->args[2])
	{
		print_error("cd: too many arguments");
		g_exit_status = 1;
		return ;
	}
/*
	path = get_cd_target(ms, cmd->args, &print_path);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		print_error_cd(cmd->args[1]);
		return (1);
	}
	update_pwd_vars(envp);
	if (print_path)
	{
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)))
			printf("%s\n", cwd);
	}
	return (0);
 */
	g_exit_status = 0;
}
