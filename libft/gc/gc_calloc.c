
#include "../libft.h"

void	*gc_calloc(size_t nmemb, size_t size, int gc_id)
{
	void	*ptr;

	ptr = gc_malloc(nmemb * size, gc_id);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
