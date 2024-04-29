/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknlist_reorder2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:30 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:27:01 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

static	void	extract_tkn_in_another_tknlist(t_token *tkn, \
		t_tknlist *tknlst_src, t_tknlist *tknlst_dest)
{
	unbound_token_in_place(tknlst_src, tkn);
	if (tkn_is_cmd(tkn->type) || tkn->type == BRACKETS)
		tknlist_addfront(tkn, tknlst_dest);
	if (tkn_is_redir(tkn->type) || tkn->type == HEREDOC)
		tknlist_addback(tkn, tknlst_dest);
}

static void	reinsert_ordered_sequence(t_tknlist *tknlst, \
		t_token *tkn_before, t_token *tkn_after, t_tknlist *reordered_lst)
{
	if (tkn_before == NULL)
	{
		tknlst->head = reordered_lst->head;
		reordered_lst->tail->next = tkn_after;
		if (tkn_after == NULL)
			tknlst->tail = reordered_lst->tail;
	}
	else
		add_tknlist_after_target(tknlst, tkn_before, reordered_lst);
}

static t_token	*reorder_sequence(t_tknlist *tknlst, t_token *cur)
{
	t_tknlist	*reordered_lst;
	t_token		*tkn_before;
	t_token		*tkn_after;
	t_token		*prev;

	init_list(&reordered_lst);
	tkn_before = cur->prev;
	tkn_after = return_end_sequence(cur);
	while (cur->next != tkn_after)
		cur = cur->next;
	while (cur != tkn_before && !tkn_is_operator(cur->type))
	{
		prev = cur->prev;
		extract_tkn_in_another_tknlist(cur, tknlst, reordered_lst);
		cur = prev;
	}
	reinsert_ordered_sequence(tknlst, tkn_before, \
		tkn_after, reordered_lst);
	return (tkn_after);
}

void	rearrange_cmd_redir_order(t_tknlist *tknlst)
{
	t_token	*cur;

	cur = tknlst->head;
	while (cur && cur->next)
	{
		if (size_sequence(cur) > 1)
			cur = reorder_sequence(tknlst, cur);
		if (cur)
			cur = cur->next;
	}
}
