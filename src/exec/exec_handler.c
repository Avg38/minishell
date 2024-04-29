/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:13 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 14:54:37 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_handler(t_shell *shell, t_btree *node, t_io fds)
{
	int		ret_status;
	bool	cmd_builtin;
	bool	pipe_is_present;

	ret_status = 0;
	cmd_builtin = is_builtin(node->cmds[0]);
	pipe_is_present = cmd_in_pipe(shell->btree, node->branch);
	if (pipe_is_present == true && cmd_builtin == true)
		ret_status = fork_builtin(&(shell->env), node, fds);
	else if (pipe_is_present == false && cmd_builtin == true)
		ret_status = exec_builtin(&(shell->env), node, fds);
	else
		ret_status = exec_bin(shell->env, node, fds);
	return (ret_status);
}
