#include "minishell.h"

static int	count_words(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			count++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	return (count);
}

static char	*malloc_word(char const *s)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	word = ft_substr(s, 0, i);
	return (word);
}

static char	**free_result(char **result, int i)
{
	while (i >= 0)
		free (result[i--]);
	free (result);
	return (NULL);
}

char	**ft_split_whitespaces(char const *s)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = ft_calloc(count_words(s) + 1, sizeof (char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			result[i] = malloc_word(s);
			if (result[i] == NULL)
				return (free_result(result, i - 1));
			i++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}

void	insert_expanded_tokens(t_shell *ms, t_token *current)
{
	char	**words;
	t_token	*new_token;
	size_t	i;
	t_token	*new_lst;
	t_token	*last_token;

	(void)ms;
	new_lst = NULL;
	words = ft_split_whitespaces(current->word);
	if (!words)
		print_error_and_exit(ms, "Expansion error", EXIT_FAILURE);
	i = 0;
	while (words[i])
	{
		new_token = ft_token_lstnew(words[i++], T_WORD);
		if (!new_token)
			return (free_char_array(words), print_error_and_exit(ms,
					"Expansion error", EXIT_FAILURE));
		ft_token_lstadd_back(&new_lst, new_token);
		last_token = new_token;
	}
	free_char_array(words);
	last_token->next = current->next;
	current->next = new_lst;
	current->word[0] = '\0';
}
