#include "minishell.h"

bool	ft_isquote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	ft_isseparator(int c)
{
	if (ft_isspace(c) || c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

bool	find_matching_quote(char quote, char *input, size_t *i)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == '\0')
		return (false);
	(*i)++;
	return (true);
}
