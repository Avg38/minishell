/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:25 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:50 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

int	is_link_sensitive(t_tkntype type)
{
	if (type == WORD || type == S_QUOTE || type == D_QUOTE \
		|| type == APPEND || type == HEREDOC || type == IN || type == OUT)
		return (1);
	return (0);
}

void	linker(t_tknlist *tkn_lst)
{
	t_token	*cur;
	t_token	*next;
	char	*new_content;

	cur = tkn_lst->head;
	while (cur)
	{
		next = cur->next;
		if (next && cur->link == 1 \
			&& is_link_sensitive(cur->type) && is_link_sensitive(next->type))
		{
			new_content = gc_strjoin(cur->content, next->content, TKN_LIST);
			if (!new_content)
				print_and_exit(ERR_MALLOC, RED, 1);
			cur->link = next->link;
			gc_del_one(cur->content, TKN_LIST);
			pop_token_in_place(tkn_lst, next);
			cur->content = new_content;
			continue ;
		}
		cur = cur->next;
	}
}
