/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:10 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/14 20:17:13 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

char	**env_to_char2(t_env *env)
{
	size_t	len;
	size_t	i;
	char	**env_2d;
	t_env	*tmp;

	tmp = env;
	i = 0;
	len = env_strlen(env);
	env_2d = (char **)malloc((len + 1) * sizeof(char *));
	if (!env_2d)
		print_and_exit(ERR_MALLOC, RED, 1);
	gc_add(env_2d, TMP);
	tmp = env;
	while (i < len)
	{
		env_2d[i] = gc_strdup(tmp->value, TMP);
		if (!env_2d[i])
			print_and_exit(ERR_MALLOC, RED, 1);
		i++;
		tmp = tmp->next;
	}
	env_2d[i] = NULL;
	return (env_2d);
}

void	exec_fd(t_io fds)
{
	if (dup2(fds.fd_in, STDIN_FILENO) == -1)
		print_and_exit(strerror(errno), RED, 1);
	if (dup2(fds.fd_out, STDOUT_FILENO) == -1)
		print_and_exit(strerror(errno), RED, 1);
	if (fds.fd_out != 1)
		close(fds.fd_out);
	if (fds.fd_in != 0)
		close(fds.fd_in);
}

void	exec_process(t_btree *node, t_env *env, t_io fds)
{
	char		*cmd_path;
	struct stat	stats;
	int			i;

	i = 3;
	cmd_path = handle_path(node, env);
	exec_fd(fds);
	if (lstat(cmd_path, &stats) != -1)
	{
		if ((stats.st_mode & S_IXUSR) && (stats.st_mode & S_IFREG))
		{
			while (i < 60)
				close(i++);
			execve(cmd_path, node->cmds, env_to_char2(env));
			print_and_exit(strerror(errno), RED, 1);
		}
		else
			print_path_error(node->cmds[0], 126, 2);
	}
	else
		print_path_error(node->cmds[0], 127, 3);
}

char	*handle_path(t_btree *node, t_env *env)
{
	char	*cmd_path;
	char	*cmd;

	cmd = node->cmds[0];
	cmd_path = NULL;
	if (!cmd)
		free_and_exit(1);
	else if (cmd && (cmd[0] == '.' || cmd[0] == '\\' || cmd[0] == '/'))
	{
		if (ft_strcmp(cmd, ".") == 0 && !node->cmds[1])
			print_path_error(cmd, 2, 5);
		else if (ft_strcmp(cmd, "..") == 0)
			print_path_error(cmd, 127, 1);
		else
			cmd_path = cmd;
	}
	else if (cmd && cmd[0] != '\0')
		cmd_path = get_cmd_path(cmd, env);
	check_path(cmd, cmd_path);
	return (cmd_path);
}

int	exec_bin(t_shell *shell, t_env *env, t_btree *node, t_io fds)
{
	shell->pid[shell->index_pid] = fork();
	if (shell->pid[shell->index_pid] == -1)
		print_and_exit("Minishell: Fork() error.\n", RED, 1);
	if (shell->pid[shell->index_pid] == 0)
		exec_process(node, env, fds);
	usleep(500);
	(shell->index_pid)++;
	if (shell->index_pid >= shell->nb_fork)
		shell->index_pid = 0;
	return (0);
}
