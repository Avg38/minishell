
#include "../libft.h"

char	*gc_strndup(char *buffer, int len, int gc_id)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = gc_malloc((i + 1) * sizeof(char), gc_id);
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
