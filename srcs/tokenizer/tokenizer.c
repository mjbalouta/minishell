#include "minishell.h"

t_token tokenizer(t_shell *ms)
{
	t_token	head;
	char	*input;

	input = ms->input;

	while (*input)
	{
		while (ft_isspace(*input))
			input++;
	}
	free(ms->input);
	ms->input = NULL;
	return (head);
}