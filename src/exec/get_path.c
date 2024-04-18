#include "../../include/minishell.h"

char	*ft_strjoin_pipex(char *s1, char *s2, char *sep)
{
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) \
		+ ft_strlen(s2) + ft_strlen(sep) + 1));
	if (!dest)
		print_and_exit(ERR_MALLOC, RED, 1);
	dest[0] = 0;
	dest = ft_strcat(dest, s1);
	dest = ft_strcat(dest, sep);
	dest = ft_strcat(dest, s2);
	return (dest);
}

void	check_path(char *cmd, char *path)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(cmd);
	if (dir && (cmd[0] == '/' \
		|| cmd[0] == '.' || cmd[ft_strlen(cmd) - 1] == '/'))
	{
		closedir(dir);
		print_path_error(cmd, 126, 4);
	}
	if (!path)
		print_path_error(cmd, 127, 1);
}

char	*check_cmd_path(char *cmd, char *path)
{
	char		*path_cmd;
	struct stat	stats;

	if (!cmd || !path)
		return (NULL);
	path_cmd = ft_strjoin_pipex(path, cmd, "/");
	if (!path_cmd)
		print_and_exit(ERR_MALLOC, RED, 1);
	if (lstat(path_cmd, &stats) == 0)
		return (gc_add(path_cmd, TMP), path_cmd);
	else
		free(path_cmd);
	return (NULL);
}

char	**find_path(t_env *env)
{
	char	*path;
	char	**path_split;

	path = env_get_value(env, "PATH", 4);
	if (path && path[0] == 0)
		return (NULL);
	path_split = gc_split(path, ':', TMP);
	if (!path_split)
		print_and_exit(ERR_MALLOC, RED, 1);
	return (path_split);
}

char *get_cmd_path(char *cmd, t_env *env)
{
	char	*exec;
	char	**path_env;
	int		i;

	i = 0;
	path_env = find_path(env);
	if (!path_env)
		print_path_error(cmd, 127, 3);
	while (path_env[i])
	{
		exec = check_cmd_path(cmd, path_env[i]);
		if (exec)
			return (exec);
		i++;
	}
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
	{
		exec = gc_strdup(cmd, TMP);
		if (!exec)
			print_and_exit(ERR_MALLOC, RED, 1);
		return (exec);
	}
	return (NULL);
}
