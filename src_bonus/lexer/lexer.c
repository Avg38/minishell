/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:22 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

/*
handle_error_lexer sert a fermer le programme proprement en cas d'erreur
*/

int	handle_error_lexer(int gc_id, char *msg)
{
	gc_clear(gc_id, free);
	ft_putstr_fd(msg, 2);
	g_status = 2;
	return (-1);
}

/*
detect_type permet de definir le type de chaque "mot" de la commande
*/

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
		return (AND);
	else if (c1 == '|' && c2 == '|')
		return (OR);
	else if (c1 == '\'')
		return (S_QUOTE);
	else if (c1 == '\"')
		return (D_QUOTE);
	else if (c1 == '(')
		return (BRACKETS);
	else if (c1 == '&' && c2 != '&')
		print_without_exit(\
			"Minishell: syntax error near unexpected token '&'\n", RED, 2);
	return (WORD);
}

/*
handle_token sert a gerer chaque "mot" de la commande selon son type
*/

void	handle_token(char *buffer, t_tknlist *list, t_tkntype type, int *i)
{
	if (type == IN || type == OUT || type == HEREDOC || type == APPEND)
		*i += handle_file(buffer, list, type);
	else if (type == PIPE)
		*i += handle_pipe(buffer, list);
	else if (type == AND || type == OR)
		*i += handle_operator(buffer, list, type);
	else if (type == S_QUOTE)
		*i += handle_s_quote(buffer, list);
	else if (type == D_QUOTE)
		*i += handle_d_quote(buffer, list);
	else if (type == BRACKETS)
		*i += handle_brackets(buffer, list);
	else if (type == WORD)
		*i += handle_word(buffer, list);
}

/*
Savoir s'il n'y a que des espaces dans la commande
*/

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

/*
Le lexer sert a determiner le type de
chaque "mot" dans la commande tape par l'utilisateur
*/

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
