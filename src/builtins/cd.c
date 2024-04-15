

#include "../../../include/minishell.h"

int	go_to_path(t_env **env)
{
	char	*env_path;
	int		ret;		// value to return

	env_path = NULL;
	env_path = get_env_value(*env, "HOME=", 4);
	if (!env_path)
		free_and_exit(1);
	else if (ft_strcmp(env_path, "") == 0)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	ret = chdir(env_path); //?
	if (ret)
	{
		ft_putstr_fd(strerror(errno), 2);  //?
		return (1);
	}
	update_pwd(env, 0); //?
	return (ret);
}

int	cd(char **cmds, t_env **env)
{
	if (cmds[1] == NULL)
		return (go_to_path(env));
	else if (cmds[2])
	{
		ft_printf_fd(2, "Minishell: cd: too many arguments\n");
		return (1);
	}
	return (process_cd(cmds, env));
}
