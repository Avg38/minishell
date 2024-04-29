/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:39 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

static int	is_charset_env(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static	t_token	*dollar_detected(t_shell *shell, char *to_expand, \
	size_t *var_len, t_tkntype type)
{
	if (to_expand[1] == '?')
	{
		*var_len = 1;
		return (create_node(type, \
				gc_itoa(shell->last_gstatus, TKN_LIST), 1));
	}
	else if (ft_isdigit(to_expand[1]))
	{
		*var_len = 1;
		return (create_node(type, "", 1));
	}
	else if (!is_charset_env(to_expand[1]))
	{
		*var_len = 1;
		return (create_node(type, \
				gc_strndup(to_expand, *var_len + 1, TKN_LIST), 1));
	}
	*var_len = ft_strlen_until_not(&to_expand[1], is_charset_env);
	return (create_node(type, \
			env_get_value(shell->env, &to_expand[1], *var_len), 1));
}

static	t_token	*dollar_undetected(char *to_expand, \
	size_t *var_len, t_tkntype type)
{
	*var_len = ft_strlen_until_char(&to_expand[0], '$') - 1;
	return (create_node(type,
			gc_strndup(to_expand, *var_len + 1, TKN_LIST), 1));
}

static void	lstadd_dollar_expansions(t_shell *shell, \
	t_tkntype tkntype, char *to_expand, t_tknlist *dollar_lst)
{
	size_t	i;
	t_token	*new_tkn;
	size_t	len_sub;

	i = 0;
	len_sub = 0;
	while (to_expand[i])
	{
		new_tkn = NULL;
		if (to_expand[i] == '$')
			new_tkn = dollar_detected(shell, &to_expand[i], &len_sub, tkntype);
		else
			new_tkn = dollar_undetected(&to_expand[i], &len_sub, tkntype);
		if (!new_tkn)
			print_and_exit(ERR_MALLOC, RED, MALLOC_E);
		add_node(dollar_lst, new_tkn);
		i += len_sub + 1;
	}
}

t_token	*expand_dollar(t_shell *shell
	, t_token *tkn_to_expand, t_tknlist *tkn_lst)
{
	t_tknlist	*dollar_lst;

	init_list(&dollar_lst);
	lstadd_dollar_expansions(shell, tkn_to_expand->type \
		, tkn_to_expand->content, dollar_lst);
	dollar_lst->tail->link = tkn_to_expand->link;
	add_tknlist_after_target(tkn_lst, tkn_to_expand, dollar_lst);
	pop_token_in_place(tkn_lst, tkn_to_expand);
	return (dollar_lst->tail);
}