/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avg38 <avg38@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:34 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 22:57:44 by avg38            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	clear_loop(void)
{
	gc_clear(TMP, free);
	gc_clear(TKN_LIST, free);
	gc_clear(B_TREE, free);
}

void	get_fork_number(t_btree *node, int *i)
{
	if (node)
	{
		if (node->type == PIPE)
			(*i)++;
		get_fork_number(node->left, i);
		get_fork_number(node->right, i);
	}
}

void	process_shell(t_shell *shell, char *line_read, int *stdin_cpy)
{
	signal(SIGQUIT, sig_handler);
	add_history(line_read);
	shell->tknlist = lexer(line_read);
	shell->btree = parser(shell);
	shell->nb_fork = 1;
	get_fork_number(shell->btree, &(shell->nb_fork));
	shell->pid = gc_calloc(sizeof(int), shell->nb_fork, TMP);
	browse_tree(shell, shell->btree, shell->io_global);
	waitlist(shell->nb_fork, shell->pid);
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

void	prompt_loop(t_shell *shell)
{
	int		stdin_cpy;
	char	*line_read;

	signal(SIGINT, sig_handler);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		stdin_cpy = dup(STDIN_FILENO);
		shell ->last_gstatus = g_status;
		g_status = 0;
		usleep(100000);
		line_read = readline(create_prompt(shell));
		g_single = 1;
		if (g_status == 130)
		{
			clear_ctrl_c(&stdin_cpy, &line_read);
			continue ;
		}
		if (!line_read)
			builtin_exit(shell, NULL);
		if (line_read && *line_read)
			process_shell(shell, line_read, &stdin_cpy);
		free(line_read);
	}
}
