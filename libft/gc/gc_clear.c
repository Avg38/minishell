
#include "../libft.h"

void	gc_clear(int gc_id, void (*del)(void*))
{
	ft_lstclear(gc_ptr(gc_id), del);
}
