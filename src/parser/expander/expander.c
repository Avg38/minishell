#include "../../../include/minishell.h"

static bool	is_dollar_expansible(t_token *tkn)
{
	if (!char_is_in_str('$', tkn->content))
		return (false);
	if (tkn->prev && tkn->prev->type == HEREDOC)
		return (false);
	if (tkn->type != WORD && tkn->type != D_QUOTE)
		return (false);
	return (true);
}

static bool	is_wildcard_expansible(t_token *tkn)
{
	if (!char_is_in_str('*', tkn->content))
		return (false);
	if (tkn->prev && tkn->prev->type == HEREDOC)
		return (false);
	if (tkn->type != WORD)
		return (false);
	return (true);
}

void	expander(t_shell *shell, t_tknlist *tknlist)
{
	t_token	*cur;

	if (g_status != 0)
		return ;
	cur = tknlist->head;
	while (cur)
	{
		if (is_dollar_expansible(cur))
			cur = expand_dollar(shell, cur, tknlist);
		cur = cur->next;
	}
	cur = tknlist->head;
	while (cur)
	{
		if (is_wildcard_expansible(cur))
			cur = expand_wildcard(cur, tknlist);
		cur = cur->next;
	}
}
