
#include "../libft.h"

char	*gc_strndup(char *buffer, int len, int id_gc)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = malloc_gc((i + 1) * sizeof(char), id_gc);
	if (!new)
		NULL;
	i = 0;
	while (buffer[i] && i < len)
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
