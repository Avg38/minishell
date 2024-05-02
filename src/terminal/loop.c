/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:34 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/02 14:48:23 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_loop(void)
{
	gc_clear(TMP, free);
	gc_clear(TKN_LIST, free);
	gc_clear(B_TREE, free);
}

void	clear_ctrl_c(int *stdin_cpy, char **line_read)
{
	if (*line_read)
		free(*line_read);
	*line_read = NULL;
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

void	clear_ctrl_z(int *stdin_cpy, char **line_read)
{
	if (*line_read)
	{
		ft_printf("%s", line_read);
		free(*line_read);
	}
	*line_read = NULL;
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

void	sig_handler(int sigcode)
{
	// static int	single = 0;
	
	if (sigcode == SIGINT)
	{
		close(STDIN_FILENO);
		g_status = 130;
		if (!single)
		{
			write(2, "\n", 1);
			single = 1;
		}
	}
	if (sigcode == SIGQUIT)
		write(2, "\b\b  \033[2D", 8);
}

void	process_shell(t_shell *shell, char *line_read, int *stdin_cpy)
{
	signal(SIGQUIT, sig_handler);
	add_history(line_read);
	shell->tknlist = lexer(line_read);
	shell->btree = parser(shell);
	browse_tree(shell, shell->btree, shell->io_global);
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
		line_read = readline(create_prompt(shell));
		single = 1;
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
