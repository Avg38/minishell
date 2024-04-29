/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:22:21 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

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

int	update_pwd(t_env **env, int slash)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	if (!slash)
		pwd = gc_strjoin("PWD=", cwd, TMP);
	else
		pwd = gc_strjoin("PWD=", "//", TMP);
	if (!pwd)
		print_and_exit(ERR_MALLOC, RED, 1);
	if (is_in_env(*env, pwd) == 0)
		env_add(pwd, env, 0);
	return (0);
}

int	go_to_path(t_env **env)
{
	char	*env_path;
	int		ret;

	env_path = NULL;
	update_oldpwd(env);
	env_path = env_get_value(*env, "HOME=", 4);
	if (!env_path)
		free_and_exit(1);
	else if (ft_strcmp(env_path, "") == 0)
		return (ft_putstr_fd("Minishell: cd: HOME not set\n", 2), 1);
	ret = chdir(env_path);
	if (ret)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	update_pwd(env, 0);
	return (ret);
}

int	process_cd(char **cmds, t_env **env)
{
	int	ret_cd;
	int	mod;

	mod = 0;
	if (update_oldpwd(env) != 0)
		return (1);
	ret_cd = chdir(cmds[1]);
	if (ret_cd < 0)
	{
		ft_printf_fd(2, "Minishell: cd: %s: %s\n", cmds[1], strerror(errno));
		return (1);
	}
	if (ft_strcmp(cmds[1], "//") == 0)
		mod = 1;
	if (update_pwd(env, mod) != 0)
		return (1);
	return (ret_cd);
}

int	cd(char **cmds, t_env **env)
{
	if (cmds[1] == NULL)
		return (go_to_path(env));
	else if (cmds[2])
		return (ft_printf_fd(2, "Minishell: cd: too many arguments\n"), 1);
	return (process_cd(cmds, env));
}
