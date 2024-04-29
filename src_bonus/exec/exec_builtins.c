/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:12 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:19 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_env **envt, t_btree *node, t_io fds)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->cmds[0], "cd") == 0)
		status = cd(node->cmds, envt);
	else if (ft_strcmp(node->cmds[0], "echo") == 0)
		status = echo(node->cmds, fds);
	else if (ft_strcmp(node->cmds[0], "pwd") == 0)
		status = pwd(fds, *envt);
	else if (ft_strcmp(node->cmds[0], "env") == 0)
		env(*envt, fds);
	else if (ft_strcmp(node->cmds[0], "export") == 0)
		status = ft_export(node->cmds, envt, fds);
	else if (ft_strcmp(node->cmds[0], "unset") == 0)
		status = unset(node->cmds, envt);
	else if (ft_strcmp(node->cmds[0], "exit") == 0)
		status = builtin_exit(singleton_shell(NULL), node->cmds);
	return (status);
}

int	fork_builtin(t_env **envt, t_btree *node, t_io fds)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	exit_code = 0;
	status = 0;
	if (pid == -1)
		print_and_exit("Minishell: Fork() error.\n", RED, 1);
	if (pid == 0)
	{
		status = exec_builtin(envt, node, fds);
		free_and_exit(status);
	}
	waitpid(pid, &status, 0);
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		exit_code = WIFEXITED(status);
	return (exit_code);
}
