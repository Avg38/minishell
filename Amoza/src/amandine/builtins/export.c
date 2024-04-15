
#include "../../../include/minishell.h"



print_sorted_env


int	print_error_export(char *args, int error)
{
	
}

/*
env_add ajoute aux env une nouvelles valeurs.
*/

int	env_add(char *value, t_env **env, int mod)
{
	t_env	*new;

	new = NULL;
	new = gc_malloc(sizeof(t_env), ENV);
	if (!new)
		free_and_exit(1);
	new->value = ft_strndup(value, ft_strlen(value), ENV);
	new->secret = mod;
	new->next = NULL;
	env_add_back(env, new);
	return (0);
}

int	export_handler(char *args, t_env **env)
{
	int	error_ret;
	int	new_env;

	error_ret = 0;
	new_env = 0;
	error_ret = is_valid_args(args);
	if (error_ret == 1)
		return (1);
	new_env = is_in_env((*env), args);
	if (new_env == 0)
	{
		if (error_ret == 2)
			env_add(args, env, 1);
		else
			env_add(args, env, 0);
	}
	return (0);
}

int	ft_export(char **args, t_env **envt, t_io fds)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_sorted_env(*envt, fds);
		return (0);
	}
	else
	{
		while (args[i] != NULL)
		{
			if (args[i][0] == 0)
			{
				print_error_export("", 1);
				return (1);
			}
			if (export_handler(args[i], envt) != 0) //rajoute une var env
				return (1);
			i++;
		}
	}
	return (0);
}
