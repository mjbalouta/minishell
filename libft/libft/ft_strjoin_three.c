#include "libft.h"

char *ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = ft_strjoin(s1, s2);
	if (!ptr1)
		return (NULL);
	ptr2 = ft_strjoin(ptr1, s3);
	free(ptr1);
	if (!ptr2)
		return (NULL);
	return (ptr2);
}
