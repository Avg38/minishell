/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avg38 <avg38@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 23:34:24 by avg38            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	oldpwd = gc_strjoin("OLDPWD=", cwd, TMP);
	if (!oldpwd)
		print_and_exit(ERR_MALLOC, RED, 1);
	if (is_in_env(*env, oldpwd) == 0)
		env_add(oldpwd, env, 0);
	return (0);
}

int	update_pwd(t_env **env, char *path)
{
	char	*pwd;

	if (!path)
		return (1);
	if (ft_strcmp(path, "-") == 0)
	{
		path = env_get_value(*env, "OLDPWD=", 7);
		if (!path)
			return (ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2), 1);
	}
	else if (path[0] == '~')
	{
		char *home = env_get_value(*env, "HOME=", 5);
		if (home)
		{
			char *tmp = gc_strdup(home, TMP);
			if (tmp)
			{
				tmp = gc_strjoin(tmp, path + 1, TMP);
				if (tmp)
				{
					path = tmp;
				}
			}
		}
	}
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	pwd = gc_strjoin("PWD=", cwd, TMP);
	if (!pwd)
		print_and_exit(ERR_MALLOC, RED, 1);
	if (is_in_env(*env, pwd) == 0)
		env_add(pwd, env, 0);
	free(pwd);
	return (0);
}

int	go_to_path(t_env **env, char *path)
{
	int		ret;

	update_oldpwd(env);
	if (!path || ft_strcmp(path, "") == 0)
	{
		path = env_get_value(*env, "HOME=", 5);
		if (!path)
			return (ft_putstr_fd("Minishell: cd: HOME not set\n", 2), 1);
	}
	ret = chdir(path);
	if (ret)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	update_pwd(env, 0);
	return (ret);
}

int	process_cd(char **cmds, t_env **env)
{
	int	ret_cd;

	if (update_oldpwd(env) != 0)
		return (1);
	ret_cd = chdir(cmds[1]);
	if (ret_cd < 0)
	{
		ft_printf_fd(2, "Minishell: cd: %s: %s\n", cmds[1], strerror(errno));
		return (1);
	}
	if (update_pwd(env, cmds[1]) != 0)
		return (1);
	return (ret_cd);
}

int	cd(char **cmds, t_env **env)
{
	if (cmds[1] == NULL)
		return (go_to_path(env, cmds[1]));
	else if (cmds[2])
		return (ft_printf_fd(2, "Minishell: cd: too many arguments\n"), 1);
	return (process_cd(cmds, env));
}
