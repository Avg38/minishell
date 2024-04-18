
#include "../libft.h"

void	*gc_malloc(size_t size, int gc_id)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add(ptr, gc_id))
		return (free(ptr), NULL);
	return (ptr);
}
