/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:22 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:43 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

static void	sort_tknlst_like_wildcard(t_tknlist *list_expnd)
{
	t_token		*cur;
	t_token		*next;
	size_t		i;
	size_t		lst_size;

	i = 0;
	lst_size = tknlist_size(list_expnd);
	while (i < lst_size)
	{
		cur = list_expnd->head;
		while (cur)
		{
			next = cur->next;
			if (next \
				&& ft_strcmp_case_insensitive(cur->content, next->content) > 0)
			{
				swap_tokens(list_expnd, cur, next);
				continue ;
			}
			cur = cur->next;
		}
		i++;
	}
}

static int	is_compatible_file_wildcard(char *file, \
	char **subs_needed, char *to_expand)
{
	if (to_expand[0] == '*' && file[0] == '.')
		return (0);
	if (to_expand[0] != '*' && !s1_is_s2_prefix(subs_needed[0], file))
		return (0);
	if (!str_contains_all_subs_ordered(file, subs_needed))
		return (0);
	if (to_expand[ft_strlen(to_expand) - 1] != '*' \
		&& !s1_is_s2_suffix(subs_needed[len_2d(subs_needed) - 1], file))
		return (0);
	return (1);
}

static void	lstadd_wildcard_expansions(t_tknlist *wildcard_lst, \
	char **subs_needed, char *to_expand)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*new_tkn;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (is_compatible_file_wildcard(entry->d_name, subs_needed, to_expand))
		{
			new_tkn = create_node(WORD, gc_strdup(entry->d_name, TKN_LIST), 0);
			if (!new_tkn)
			{
				closedir(dir);
				print_and_exit(ERR_MALLOC, RED, 1);
			}
			add_node(wildcard_lst, new_tkn);
		}
		entry = readdir(dir);
	}
	if (dir)
		closedir(dir);
}

t_token	*expand_wildcard(t_token *tkn_toexpand, t_tknlist *tkn_lst)
{
	t_tknlist	*wildcard_lst;
	char		**splitted;

	splitted = gc_split(tkn_toexpand->content, '*', TMP);
	init_list(&wildcard_lst);
	lstadd_wildcard_expansions(wildcard_lst, splitted, tkn_toexpand->content);
	if (!wildcard_lst->head)
		return (tkn_toexpand);
	sort_tknlst_like_wildcard(wildcard_lst);
	add_tknlist_after_target(tkn_lst, tkn_toexpand, wildcard_lst);
	pop_token_in_place(tkn_lst, tkn_toexpand);
	tkn_toexpand = wildcard_lst->head;
	gc_clear(TMP, free);
	return (wildcard_lst->tail);
}
