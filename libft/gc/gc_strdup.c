
#include "../libft.h"

char	*gc_strdup(const char *str, int id_gc)
{
	char	*result;
	size_t	length;

	length = ft_strlen(str);
	result = (char *)malloc_gc((length + 1) * sizeof(char), id_gc);
	if (!result)
		return (NULL);
	length = 0;
	while (str[length] != '\0')
	{
		result[length] = str[length];
		length++;
	}
	result[length] = '\0';
	return (result);
}
