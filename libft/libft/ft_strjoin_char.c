#include "libft.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	ft_memcpy(new_str, s, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}
