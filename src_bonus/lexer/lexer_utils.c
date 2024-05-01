/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sei <sei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:20 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/01 20:11:58 by sei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

// char	*ft_strndup(char *buffer, int len, t_gc_id id)
// {
// 	char	*new;
// 	int		i;

// 	i = 0;
// 	while (buffer[i] && i < len)
// 		i++;
// 	new = gc_malloc((i + 1) * sizeof(char), id);
// 	if (!new)
// 		print_and_exit(ERR_MALLOC, RED, 1);
// 	i = 0;
// 	while (buffer[i] && i < len)
// 	{
// 		new[i] = buffer[i];
// 		i++;
// 	}
// 	new[i] = 0;
// 	return (new);
// }

int	is_operator(const char c1, const char c2)
{
	if (c1 == '|' && c2 != '|')
		return (1);
	else if (c1 == '&' && c2 == '&')
		return (1);
	else if (c1 == '|' && c2 == '|')
		return (1);
	return (0);
}

int	detect_error_type(const char c)
{
	if (c == '(' || c == ';' || c == '\\')
		return (handle_error_lexer(TKN_LIST, ERR_WRONG_CHAR));
	return (0);
}
