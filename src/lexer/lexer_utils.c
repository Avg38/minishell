/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:20 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 20:50:24 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
