#include "../libft.h"

size_t	len_2d(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
