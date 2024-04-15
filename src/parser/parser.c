#include "../../include/minishell.h"

void	set_token_index(t_token *cur)
{
	size_t	i;

	i = 0;
	while (cur)
	{
		cur->index = i;
		if (is_redir_tkn(cur->type) || cur->type == HEREDOC)
			cur->priority = 1;
		if (cur->type == PIPE)
			cur->priority = 3;
		else if (is_logical_op_tkn(cur->type))
			cur->priority = 4;
		i++;
		cur = cur->next;
	}
}

t_btree	*parser(t_shell *shell)
{
	if (g_status != 0 || !shell->tknlist)
		return (clear_loop(), NULL);
	verify_syntax_tknlist(shell->tknlist);
	if (g_status != 0)
		return (clear_loop(), NULL);
	reducer(shell->tknlist->head);
	expander(shell, shell->tknlist);
	linker(shell->tknlist);
	rearrange_cmd_redir_order(shell->tknlist);
	set_tpken_index(shell->tknlist->head);
	return (create_bin_tree(shell->tknlist));
}

/*
Parser need to return a binary tree or a list.
*/
