
#include "../libft.h"

t_list	*gc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *),
	int gc_id)
{
	t_list	*nlst;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	nlst = NULL;
	while (lst)
	{
		elem = gc_lstnew(f(lst->content), gc_id);
		if (!elem)
		{
			gc_clear(gc_id, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, elem);
		lst = lst->next;
	}
	return (nlst);
}
