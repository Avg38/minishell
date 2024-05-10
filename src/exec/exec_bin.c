/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:10 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 20:50:22 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	exec_fd(fds);
	cmd_path = handle_path(node, env);
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

int	exec_bin(t_shell *shell, t_env *env, t_btree *node, t_io fds)
{
	int				status;
	int				exit_code;
	static int		i = 0;

	status = 0;
	exit_code = 0;
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
		print_and_exit("Minishell: Fork() error.\n", RED, 1);
	if (shell->pid[i] == 0)
		exec_process(node, env, fds);
	i++;
	if (i >= shell->nb_fork)
		i = 0;
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}
