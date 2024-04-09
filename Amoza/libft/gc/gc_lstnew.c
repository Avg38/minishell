
#include "../libft.h"

t_list	*gc_lstnew(void *content, int gc_id)
{
	t_list	*element;

	element = (t_list *)gc_malloc(sizeof(t_list), gc_id);
	if (element == NULL)
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}
