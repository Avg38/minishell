
#include "../libft.h"

char	*gc_strmapi(char const *s, char (*f)(unsigned int, char), int gc_id)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = gc_calloc(len + 1, 1, gc_id);
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	return (ptr);
}
