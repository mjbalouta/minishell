#include "minishell.h"

static char	*build_env_str(t_envp *lst, bool export_style)
{
	char	*result_part;
	char	*result;

	if (lst->value)
	{
		if (export_style)
		{
			result_part = ft_strjoin_three("declare -x ", lst->key, "=\"");
			if (!result_part)
				return (NULL);
			result = ft_strjoin_three(result_part, lst->value, "\"");
			free(result_part);
			return (result);
		}
		result = ft_strjoin_three(lst->key, "=", lst->value);
		return (result);
	}
	if (export_style)
	{
		result = ft_strjoin("declare -x ", lst->key);
		return (result);
	}
	result = ft_strdup(lst->key);
	return (result);
}

/**
 * @brief Converts the environment variable linked list to a char array.
 *
 * This function traverses the shell's environment variable linked list and 
 * creates a newly allocated, NULL-terminated array of strings. If 
 * @p export_style is true, each entry is formatted for shell export
 * (e.g., "declare -x KEY=\"VALUE\"" or "declare -x KEY" if value is NULL); 
 * otherwise, entries are in standard "KEY=VALUE" or just "KEY" format. 
 * The caller is responsible for freeing the returned array and each of its 
 * strings using free_char_array().
 *
 * @param ms Pointer to the shell structure containing the envp list.
 * @param export_style If true, formats output for export; otherwise, standard 
 * key=value.
 * @return A newly allocated NULL-terminated array of strings representing 
 * environment variables.
 */
char	**ft_envp_lst_to_char_array(t_shell *ms, bool export_style)
{
	char	**out;
	size_t	i;
	t_envp	*lst;

	i = 0;
	lst = ms->envp;
	out = ft_calloc(ft_envp_lstsize(lst, !export_style) + 1, sizeof(*out));
	if (!out)
		print_error_and_exit(ms, "Memory allocation error\n", EXIT_FAILURE);
	while (lst)
	{
		if (lst->value || export_style)
		{
			out[i] = build_env_str(lst, export_style);
			if (!out[i++])
			{
				free_char_array(out);
				print_error_and_exit(ms, "Memory allocation error\n",
					EXIT_FAILURE);
			}
		}
		lst = lst->next;
	}
	out[i] = NULL;
	return (out);
}
