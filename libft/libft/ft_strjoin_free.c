#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *new_str;
	
	new_str = ft_strjoin(s1, s2);
	free(s1);
	if (!new_str)
		return (NULL);
	return new_str;
}
