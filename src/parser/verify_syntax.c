/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:32 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:01:09 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	printfd_err(int fd, int ret, char *err_msg, char *issue)
{
	if (issue)
		ft_printf_fd(fd, "%s%s `%s'%s\n", RED, err_msg, issue, RESET);
	else
		ft_printf_fd(fd, "%s%s%s\n", RED, err_msg, RESET);
	return (ret);
}

static int	verif_head(t_token *head)
{
	if (tkn_is_operator(head->type))
		return (printfd_err(2, 2, ERR_NEAR_TOKEN, head->content));
	else if (head->type == BRACKETS && brackets_is_empty(head->content))
		return (printfd_err(2, 2, ERR_NEAR_TOKEN, ")"));
	return (0);
}

static int	verif_tail(t_token *tail)
{
	if (tail->type == PIPE)
		return (printfd_err(2, 2, ERR_OPEN_PIPE, NULL));
	if (tail->type == AND || tail->type == OR)
		return (printfd_err(2, 2, ERR_OPEN_LOGICAL_OP, NULL));
	if (tkn_is_redir(tail->type) || tail->type == HEREDOC)
		return (printfd_err(2, 2, ERR_NEAR_TOKEN, "newline"));
	if (tail->type == BRACKETS && brackets_is_empty(tail->content))
		return (printfd_err(2, 2, ERR_NEAR_TOKEN, "("));
	return (0);
}

static int	verif_body(t_token *curr)
{
	while (curr && curr->next && g_status == 0)
	{
		if ((tkn_is_operator(curr->type) || tkn_is_redir(curr->type))
			&& tkn_is_operator(curr->next->type))
			return (printfd_err(2, 2, ERR_NEAR_TOKEN, curr->next->content));
		if (tkn_is_redir(curr->type) && curr->next->type == WORD
			&& char_is_in_str('*', curr->next->content))
			return (printfd_err(2, 1, ERR_STAR_TOKEN, NULL));
		if (curr->type == BRACKETS && brackets_is_empty(curr->content) == 1)
			return (printfd_err(2, 2, ERR_NEAR_TOKEN, "("));
		curr = curr->next;
	}
	return (0);
}

void	verify_syntax_tknlist(t_tknlist *lst)
{
	int	exit_status;

	exit_status = verif_head(lst->head);
	if (exit_status != 0)
	{
		g_status = exit_status;
		return ;
	}
	exit_status = verif_body(lst->head);
	if (exit_status != 0)
	{
		g_status = exit_status;
		return ;
	}
	g_status = verif_tail(lst->tail);
}
