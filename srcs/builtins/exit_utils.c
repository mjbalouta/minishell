#include "minishell.h"

void	skip_whitespaces(char **str)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
}

int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
		if (**str < '0' || **str > '9')
			return (0);
	}
	return (sign);
}
