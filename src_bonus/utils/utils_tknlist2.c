/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tknlist2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:43 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:30 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	add_after_another(t_tknlist *list, t_token *tkn1, t_token *tkn2)
{
	tkn2->next = tkn1->next;
	tkn1->next = tkn2;
	tkn2->prev = tkn1;
	if (tkn1 == list->tail)
		list->tail = tkn2;
}

void	pop_token_in_place(t_tknlist *list_tkn, t_token *to_pop)
{
	if (to_pop == NULL)
		return ;
	if (to_pop != list_tkn->head)
		(to_pop->prev)->next = to_pop->next;
	else
		list_tkn->head = to_pop->next;
	if (to_pop != list_tkn->tail)
		(to_pop->next)->prev = to_pop->prev;
	else
		list_tkn->tail = to_pop->prev;
	if (to_pop->content)
		gc_del_one(to_pop->content, TKN_LIST);
	gc_del_one(to_pop, TKN_LIST);
}

void	add_tknlist_after_target(t_tknlist *lst1 \
	, t_token *tkn_flag, t_tknlist *lst2)
{
	if (!lst1 || !lst1->head || !tkn_flag || !lst2 || !lst2->head)
		return ;
	if (tkn_flag == lst1->tail)
		lst1->tail = lst2->tail;
	else
	{
		(lst2->tail)->next = tkn_flag->next;
		(tkn_flag->next)->prev = lst2->tail;
	}
	(lst2->head)->prev = tkn_flag;
	tkn_flag->next = (lst2->head);
}

void	swap_tokens(t_tknlist *lst, t_token *tkn1, t_token *tkn2)
{
	t_token	*tmp_prev;

	if (tkn1 == NULL || tkn2 == NULL \
		|| lst == NULL || lst->head == NULL || lst->tail == NULL)
		return ;
	tmp_prev = tkn1->prev;
	if (tkn1 == lst->head)
		lst->head = tkn2;
	else
		(tkn1->prev)->next = tkn2;
	if (tkn2 == lst->tail)
		lst->tail = tkn1;
	else
		(tkn2->next)->prev = tkn2;
	tkn1->prev = tkn2;
	tkn1->next = tkn2->next;
	tkn2->prev = tmp_prev;
	tkn2->next = tkn1;
}

size_t	tknlist_size(t_tknlist *tknlist)
{
	t_token	*cur;
	size_t	i;

	cur = tknlist->head;
	i = 0;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}
