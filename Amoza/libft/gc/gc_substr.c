
#include "../libft.h"

char	*gc_substr(char const *s, unsigned int start, size_t len, int id_gc)
{
	char	*dest;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dest = (char *)malloc_gc(sizeof(char), id_gc);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (start + len > s_len)
		len = s_len - start;
	dest = (char *)malloc_gc((len + 1) * sizeof(char), id_gc);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, &s[start], len);
	dest[len] = '\0';
	return (dest);
}
