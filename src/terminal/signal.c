/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:46:14 by avg38             #+#    #+#             */
/*   Updated: 2024/05/14 20:02:17 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (!g_single)
		{
			write(2, "\n", 1);
			g_single = 1;
		}
	}
	if (sigcode == SIGQUIT)
	{
		write(2, "\b\b  \033[2D", 8);
		g_status = 131;
	}
}

int	waitlist(int nb_fork, int *pid)
{
	int		i;
	int		status;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (i < nb_fork)
	{
		status = 0;
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
	}
	return (exit_status);
}
