/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:09 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 14:50:10 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_child(pid_t pid)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	waitpid(pid, &status, 0);
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

void	browse_tree(t_shell *shell, t_btree *node, t_io io_inherited)
{
	if (!node || g_status == 130)
		return ;
	if (tkn_is_logic(node->type))
		cross_operator(shell, node, io_inherited);
	else if (node->type == PIPE)
		cross_pipe(shell, node, io_inherited);
	else if (node->type == IN)
		cross_input(shell, node, io_inherited);
	else if (node->type == OUT || node->type == APPEND)
		cross_output(shell, node, io_inherited);
	else if (node->type == HEREDOC)
		cross_heredoc(shell, node, io_inherited);
	else if (node->type == BRACKETS)
		g_status = cross_brackets(shell, node, io_inherited);
	else if (node->type == WORD)
		g_status = exec_handler(shell, node, io_inherited);
}
