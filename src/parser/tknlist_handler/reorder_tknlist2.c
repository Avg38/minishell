
#include "../../../include/minishell.h"

t_token	*return_end_sequence(t_token *begin_seq)
{
	t_token	*cur;

	cur = begin_seq;
	while (cur && !is_operator_tkn(cur->type))
	{
		cur = cur->next;
	}
	return (cur);
}

size_t	size_sequence(t_token *begin_seq)
{
	t_token	*cur;
	size_t	i;

	cur = begin_seq;
	i = 0;
	while (cur && !is_operator_tkn(cur->type))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}
