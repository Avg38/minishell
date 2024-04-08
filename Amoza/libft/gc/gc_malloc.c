
#include "../libft.h"

void	*gc_malloc(size_t size, int id_gc)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!add_to_garbage(ptr, id_gc))
		return (free(ptr), NULL);
	return (ptr);
}
