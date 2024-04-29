/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:40 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:31 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	depth_first_search(t_btree *node, void (*visit)(t_btree *, int))
{
	static int	depth = -1;

	depth++;
	if (node)
	{
		depth_first_search(node->left, visit);
		visit(node, depth);
		depth_first_search(node->right, visit);
	}
	depth--;
}

void	root_first_search(t_btree *node, void (*visit)(t_btree *, int))
{
	static int	depth = -1;

	depth++;
	if (node)
	{
		visit(node, depth);
		root_first_search(node->left, visit);
		root_first_search(node->right, visit);
	}
	depth--;
}

void	display_node(t_btree *node, int depth)
{
	size_t	i;

	i = 0 ;
	if (!node)
		printf("Node is NULL\n");
	printf("DEPTH: %d\n", depth);
	printf("Type: %d\n", node->type);
	if (node->cmds)
	{
		printf("Cmds :");
		while (node->cmds && node->cmds[i])
		{
			printf("%s   ", node->cmds[i]);
			i++;
		}
	}
	printf("\n\n");
}
