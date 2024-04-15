#include "../libft.h"

char	**dup_2d(char **tab)
{
	size_t	i;
	size_t	size;
	char	**dup;

	i = 0;
	size = len_2d(tab) + 1;
	dup = (char **)ft_calloc(size, sizeof(char *));
	if (!dup)
		return (NULL);
	while (i < size - 1)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (free_2d(dup), NULL);
		i++;
	}
	return (dup);
}
