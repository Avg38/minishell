#include "../libft.h"

void	free_2d(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}
