/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:07 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:18 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	cross_input(t_shell *shell, t_btree *node \
	, t_io io_inherited)
{
	t_io	io_transmitted;

	if (io_inherited.fd_in != 0)
		close(io_inherited.fd_in);
	ft_memcpy(&io_transmitted, &io_inherited, sizeof(t_io));
	io_transmitted.fd_in = open(node->cmds[0], O_RDONLY);
	if (io_transmitted.fd_in == -1)
		return (print_strerror(node->cmds[0], RED, 1));
	browse_tree(shell, node->left, io_transmitted);
	if (io_transmitted.fd_in != 0)
		close(io_transmitted.fd_in);
}

void	cross_output(t_shell *shell, t_btree *node \
	, t_io io_inherited)
{
	t_io	io_transmitted;

	if (io_inherited.fd_out != 0 && io_inherited.fd_out != 1)
		close(io_inherited.fd_out);
	ft_memcpy(&io_transmitted, &io_inherited, sizeof(t_io));
	if (node->type == OUT)
		io_transmitted.fd_out = open(node->cmds[0] \
			, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		io_transmitted.fd_out = open(node->cmds[0] \
			, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (io_transmitted.fd_out == -1)
	{
		print_strerror(node->cmds[0], RED, 1);
		return ;
	}
	browse_tree(shell, node->left, io_transmitted);
	if (io_transmitted.fd_out != 0 && io_transmitted.fd_out != 1)
		close(io_transmitted.fd_out);
}

void	cross_pipe(t_shell *shell, t_btree *node, t_io io_inherited)
{
	int		fd_pipe[2];
	t_io	io_transmitted;

	ft_memcpy(&io_transmitted, &io_inherited, sizeof(t_io));
	if (pipe(fd_pipe) == -1)
		return (print_strerror("pipe", RED, 1));
	io_transmitted.fd_out = fd_pipe[FD_WRITE];
	browse_tree(shell, node->left, io_transmitted);
	close(fd_pipe[FD_WRITE]);
	io_transmitted.fd_in = fd_pipe[FD_READ];
	io_transmitted.fd_out = io_inherited.fd_out;
	browse_tree(shell, node->right, io_transmitted);
	close(fd_pipe[FD_READ]);
}

void	cross_operator(t_shell *shell, t_btree *node \
	, t_io io_inherited)
{
	browse_tree(shell, node->left, io_inherited);
	if ((node->type == AND && g_status == 0)
		|| (node->type == OR && g_status != 0))
		browse_tree(shell, node->right, io_inherited);
}

int	cross_brackets(t_shell *shell, t_btree *node, t_io io_inherited)
{
	pid_t	pid;
	char	*new_prompt;

	pid = fork();
	if (pid == -1)
		print_and_exit("Minishell : Fork error\n", RED, 1);
	if (pid == 0)
	{
		new_prompt = gc_strdup(node->cmds[0], TMP);
		gc_clear(B_TREE, free);
		shell->btree = NULL;
		shell->tknlist = lexer(new_prompt);
		shell->btree = parser(shell);
		browse_tree(shell, shell->btree, io_inherited);
		free_and_exit(g_status);
	}
	return (wait_child(pid));
}
