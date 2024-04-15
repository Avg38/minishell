
#include "../libft.h"

void	*gc_calloc(size_t nmemb, size_t size, int id_gc)
{
	void	*ptr;

	ptr = gc_malloc(nmemb * size, id_gc);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
