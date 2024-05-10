/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:34 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 20:51:04 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

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

void	sig_handler(int sigcode)
{
	if (sigcode == SIGINT)
	{
		close(STDIN_FILENO);
		g_status = 130;
	}
	if (sigcode == SIGQUIT)
		write(2, "\b\b  \033[2D", 8);
	if (sigcode == SIGTSTP)
		write(2, "\b\b  \033[2D", 8);
}

int	waitlist(int nb_fork, int *pid)
{
	int		i;
	int		status;
	int		exit_status;

	i = 0;
	exit_status = 0;
	status = 0;
	while (i < nb_fork)
	{
		waitpid(pid[i], &status, 0);
		if (WCOREDUMP(status) && WTERMSIG(status) == 11)
		{
			g_status = 139;
			ft_putendl_fd("Segmentation fault (core dumped)", 2);
		}
		if (WCOREDUMP(status) && WTERMSIG(status) == 3)
			ft_putendl_fd("Quit (core dumped)", 2);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		i++;
		status = 0;
	}
	return (exit_status);
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
