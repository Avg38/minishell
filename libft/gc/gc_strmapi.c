
#include "../libft.h"

char	*gc_strmapi(char const *s, char (*f)(unsigned int, char), int id_gc)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = calloc_gc(len + 1, 1, id_gc);
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	return (ptr);
}
