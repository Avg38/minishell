
#include "../libft.h"

t_list	**gc_ptr(int gc_id)
{
	static t_list	*collector[GC_SIZE];

	return (&collector[gc_id]);
}
