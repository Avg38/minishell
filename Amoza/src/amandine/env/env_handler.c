#include "../../include/minishell.h"

t_env	*init_env(char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!env_array)
		return (NULL);
	i = 0;
	env = NULL;
	new = NULL;
	while (env_array[i] != NULL)
	{
		new = gc_malloc(sizeof(t_env), ENV);
		if (!new)
			free_and_exit(1);
		new->value = ft_strndup(env_array[i], ft_strlen(env_array[i], ENV));
		if (!new->value)
			print_and_exit(MSG_MALLOC_ERR, RED, 1);
		new->value = NULL;
		new->secret = 0;
		env_add_back(&env, new);
		i++;
	}
	return (env);
}
