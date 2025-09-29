#include "libft.h"

char *ft_strjoin_five(const char *s1, const char *s2, const char *s3, 
	const char *s4, const char *s5)
{
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;

	ptr1 = ft_strjoin(s1, s2);
	if (!ptr1)
		return (NULL);
	ptr2 = ft_strjoin(ptr1, s3);
	free(ptr1);
	if (!ptr2)
		return (NULL);
	ptr3 = ft_strjoin(ptr2, s4);
	free(ptr2);
	if (!ptr3)
		return (NULL);
	ptr4 = ft_strjoin(ptr3, s5);
	free(ptr3);
	if (!ptr4)
		return (NULL);
	return (ptr4);
}
