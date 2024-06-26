/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:27 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:55 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

int	type_need_reducing(t_tkntype type)
{
	if (type == IN || type == OUT || type == APPEND \
		|| type == HEREDOC || type == D_QUOTE \
		|| type == S_QUOTE || type == BRACKETS)
		return (1);
	return (0);
}

static char	*reduce_content(t_token *tkn)
{
	char	*new_content;

	if (tkn->type == IN || tkn->type == OUT)
	{
		new_content = remove_substr(tkn->content, 0, 1 \
			+ ft_strlen_until_not(&tkn->content[1], ft_isspace));
		if (new_content[0] == '"')
			new_content = ft_strcut(new_content, 1, 1);
	}
	if (tkn->type == HEREDOC || tkn->type == APPEND)
		new_content = remove_substr(tkn->content, 0, 2 \
			+ ft_strlen_until_not(&tkn->content[2], ft_isspace));
	else if (tkn->type == D_QUOTE \
		|| tkn->type == S_QUOTE || tkn->type == BRACKETS)
		new_content = ft_strcut(tkn->content, 1, 1);
	return (new_content);
}

void	reducer(t_token	*tkn)
{
	char	*new_content;

	if (g_status != 0)
		return ;
	while (tkn)
	{
		if (type_need_reducing(tkn->type))
		{
			new_content = reduce_content(tkn);
			if (!new_content)
				print_and_exit(ERR_MALLOC, RED, 1);
			gc_add(new_content, TKN_LIST);
			gc_del_one(tkn->content, TKN_LIST);
			tkn->content = new_content;
		}
		tkn = tkn->next;
	}
}
