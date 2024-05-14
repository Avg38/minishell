/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/14 13:44:10 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_error_lexer(int gc_id, char *msg)
{
	gc_clear(gc_id, free);
	ft_putstr_fd(msg, 2);
	g_status = 2;
	return (-1);
}

int	detect_type(const char c1, const char c2)
{
	if (c1 == '<' && c2 != '<')
		return (IN);
	else if (c1 == '>' && c2 != '>')
		return (OUT);
	else if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	else if (c1 == '>' && c2 == '>')
		return (APPEND);
	else if (c1 == '|' && c2 != '|')
		return (PIPE);
	else if (c1 == '&' && c2 == '&')
		detect_operator_type(c1, c2);
	else if (c1 == '|' && c2 == '|')
		detect_operator_type(c1, c2);
	else if (c1 == '\'')
		return (S_QUOTE);
	else if (c1 == '\"')
		return (D_QUOTE);
	else if (c1 == '(')
		return (BRACKETS);
	else if (c1 == '&' && c2 != '&')
		detect_operator_type(c1, c2);
	return (WORD);
}

void	handle_token(char *buffer, t_tknlist *list, t_tkntype type, int *i)
{
	if (type == IN || type == OUT || type == HEREDOC || type == APPEND)
		*i += handle_file(buffer, list, type);
	else if (type == PIPE)
		*i += handle_pipe(buffer, list);
	else if (type == S_QUOTE)
		*i += handle_s_quote(buffer, list);
	else if (type == D_QUOTE)
		*i += handle_d_quote(buffer, list);
	else if (type == BRACKETS)
		*i += handle_brackets(buffer, list);
	else if (type == WORD)
		*i += handle_word(buffer, list);
}

int	is_only_space(char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer)
		return (1);
	while (buffer[i])
	{
		if (!ft_isspace(buffer[i]))
			return (0);
		i++;
	}
	return (1);
}

t_tknlist	*lexer(char *buffer)
{
	int			i;
	t_tkntype	type;
	t_tknlist	*list;

	if (!buffer || g_status != 0 || is_only_space(buffer) == 1)
		return (NULL);
	init_list(&list);
	i = 0;
	while (buffer[i])
	{
		if (!ft_isspace(buffer[i]))
		{
			if (detect_error_type(buffer[i]) == -1)
				break ;
			type = detect_type(buffer[i], buffer[i + 1]);
			handle_token(&buffer[i], list, type, &i);
			if (g_status != 0)
				break ;
		}
		else
			i++;
	}
	return (list);
}
