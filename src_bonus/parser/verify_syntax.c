/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:32 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/14 13:24:11 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

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
	{
		printfd_err(2, 2, ERR_NEAR_TOKEN, head->content);
		return (2);
	}
	else if (head->type == BRACKETS && brackets_is_empty(head->content))
	{
		printfd_err(2, 2, ERR_NEAR_TOKEN, ")");
		return (2);
	}
	return (0);
}

static int	verif_tail(t_token *tail)
{
	if (tail->type == PIPE)
	{
		printfd_err(2, 2, ERR_OPEN_PIPE, NULL);
		return (2);
	}
	if (tail->type == AND || tail->type == OR)
	{
		printfd_err(2, 2, ERR_OPEN_LOGICAL_OP, NULL);
		return (2);
	}
	if (tkn_is_redir(tail->type) || tail->type == HEREDOC)
	{
		printfd_err(2, 2, ERR_NEAR_TOKEN, "newline");
		return (2);
	}
	if (tail->type == BRACKETS && brackets_is_empty(tail->content))
	{
		printfd_err(2, 2, ERR_NEAR_TOKEN, "(");
		return (2);
	}
	return (0);
}

static int	verif_body(t_token *curr)
{
	while (curr && curr->next && g_status == 0)
	{
		if ((tkn_is_operator(curr->type) || tkn_is_redir(curr->type))
			&& tkn_is_operator(curr->next->type))
		{
			printfd_err(2, 2, ERR_NEAR_TOKEN, curr->next->content);
			return (2);
		}
		if (tkn_is_redir(curr->type) && curr->next->type == WORD \
			&& char_is_in_str('*', curr->next->content))
		{
			printfd_err(2, 1, ERR_STAR_TOKEN, NULL);
			return (1);
		}
		if (curr->type == BRACKETS && brackets_is_empty(curr->content) == 1)
		{
			printfd_err(2, 2, ERR_NEAR_TOKEN, "(");
			return (2);
		}
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
