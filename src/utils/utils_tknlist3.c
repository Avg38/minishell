#include "../../include/minishell.h"

void	unbound_token_in_place(t_tknlist *list_tkn, t_token *to_pop)
{
	if (!to_pop)
		return ;
	if (to_pop != list_tkn->head)
		(to_pop->prev)->next = to_pop->next;
	else
		list_tkn->head = to_pop->next;
	if (to_pop != list_tkn->tail)
		(to_pop->next)->prev = to_pop->prev;
	else
		list_tkn->tail = to_pop->prev;
}

void	tknlist_addfront(t_token *cur, t_tknlist *tknlist)
{
	if (!cur || !tknlist)
		return ;
	cur->prev = NULL;
	cur->next = tknlist->head;
	if (tknlist->head)
		tknlist->head->prev = cur;
	if (!tknlist->tail)
		tknlist->tail = cur;
	tknlist->head = cur;
}

void	tknlist_addback(t_token *cur, t_tknlist *tknlist)
{
	if (!cur || !tknlist)
		return ;
	cur->next = NULL;
	if (!tknlist->head)
	{
		tknlist->head = cur;
		tknlist->tail = cur;
	}
	else
	{
		cur->prev = tknlist->tail;
		tknlist->tail->next = cur;
		tknlist->tail = cur;
	}
}
