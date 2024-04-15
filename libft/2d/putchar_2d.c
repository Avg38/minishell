#include "../libft.h"

void	putchar_2d(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
