
#include "../libft.h"

char	*gc_strjoin(char const *s1, char const *s2, int gc_id)
{
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = (char *)gc_malloc((ft_strlen(s1) \
		+ ft_strlen(s2) + 1) * sizeof(char), gc_id);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
	return (dest);
}
