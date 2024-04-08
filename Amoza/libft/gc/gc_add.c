
#include "../libft.h"

void	*gc_add(void *ptr, int gc_id)
{
	t_list	*element;

	if (gc_id < 0 || gc_id >= GC_SIZE)
		return (NULL);
	element = ft_lstnew(ptr);
	if (element == NULL)
		return (free(ptr), NULL);
	ft_lstadd_front(garbage_ptr(gc_id), element);
}
