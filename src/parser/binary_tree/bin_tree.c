#include "../../../include/minishell.h"

t_token	*find_prio_token(t_token *cur)
{
	t_token	*target;

	target = cur;
	while (cur && cur->used_flag != 1)
	{
		if (cur->priority > 0 && cur->priority >= target->priority)
			target = cur;
		cur = cur->next;
	}
	return (target);
}

t_btree	*place_in_tree(t_btree *node, t_btree *toplace, int index)
{
	if (node == NULL)
		return (toplace);
	if (index < node->branch)
		node->left = place_in_tree(node->left, toplace, index);
	else if (index > node->branch)
		node->right = place_in_tree(node->right, toplace, index);
	return (node);
}

/*
Pas sur de comprendre ...
*/

t_btree	*btree_new(t_token *tkn_to_convert)
{
	t_btree	*node; //tree_el ? or node ?

	tkn_to_convert->used_flag = 1;
	node = gc_calloc(1, sizeof(t_btree), B_TREE);
	if (!node)
		print_and_exit(ERR_MALLOC, RED, 1);
	node->branch = tkn_to_convert->index;
	node->type = tkn_to_convert->type;
	if (tkn_is_cmd(tkn_to_convert->type))
	{
		node->type = WORD;
		node->cmds = extract_cmd_argv(tkn_to_convert);
	}
	else
		node->cmds = strdup_in_newchar2(tkn_to_convert->content);
	return (node);
}

/*
tknlst can be named collection...
*/

t_btree	*create_bin_tree(t_tknlist *tknlst)
{
	t_token	*prio_tkn;
	t_btree	*btree_root;

	if (g_status != 0)
		return (NULL);
	btree_root = NULL;
	while (tknlst->head)
	{
		if (tknlst->head->used_flag == 1 || tknlst->head->content[0] == 0)
		{
			pop_token_in_place(tknlst, tknlst->head);
			continue ;
		}
		prio_tkn = find_prio_token(prio_tkn);
		if (!btree_root)
			btree_root = btree_new(prio_tkn);
		else
			place_in_tree(btree_root, btree_new(prio_tkn), prio_tkn->index);
		prio_tkn->used_flag = 1;
	}
	gc_clear(TKN_LIST, free);
	return (btree_root);
}
