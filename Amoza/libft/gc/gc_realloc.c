
#include "../libft.h"

static size_t	max_value_size_t(size_t v1, size_t v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

void	*gc_realloc(void *ptr, size_t old_size, size_t new_size, int id_gc)
{
	size_t	size;
	void	*new;

	if (new_size == 0)
		return (del_one_garbage(ptr, id_gc), NULL);
	size = (size_t)max_value_size_t(old_size, new_size);
	new = gc_malloc(new, ptr, size);
	if (ptr)
		ft_memcpy(new, ptr, size);
	gc_del_one(ptr, id_gc);
	return (new);
}
