/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:17 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:21 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	handle_file(char *buffer, t_tknlist *list, t_tkntype type)
{
	int	i;

	if (type == APPEND || type == HEREDOC)
		i = 2;
	else
		i = 1;
	if (!add_node(list, create_node(type, ft_strndup(buffer, i, TKN_LIST), 1)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (i);
}

int	handle_pipe(char *buffer, t_tknlist *list)
{
	if (!add_node(list, create_node(PIPE, ft_strndup(buffer, 1, TKN_LIST), 0)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (1);
}

int	handle_operator(char *buffer, t_tknlist *list, t_tkntype type)
{
	if (!add_node(list, create_node(type, ft_strndup(buffer, 2, TKN_LIST), 0)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (2);
}

int	handle_s_quote(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 1;
	link = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'')
			break ;
		i++;
	}
	if (buffer[i] == 0)
		return (handle_error_lexer(TKN_LIST, ERR_QUOTES));
	if (ft_isspace(buffer[i + 1]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(S_QUOTE, ft_strndup(buffer, i + 1, TKN_LIST), link)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (i + 1);
}

int	handle_d_quote(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 1;
	link = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\"')
			break ;
		i++;
	}
	if (buffer[i] == 0)
		return (handle_error_lexer(TKN_LIST, ERR_QUOTES));
	if (ft_isspace(buffer[i + 1]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(D_QUOTE, ft_strndup(buffer, i + 1, TKN_LIST), link)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (i + 1);
}
