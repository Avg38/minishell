#include "../../include/minishell.h"

size_t	env_size(char *env)
{
	size_t	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

int	search_and_unset(char **value, t_env **env, int index)
{
	t_env	*tmp;
	t_env	*cur;
	t_env	*node;

	cur = *env;
	while (cur && cur->next)
	{
		if (ft_strncmp(value[index], cur->next->value,
				env_size(cur->next->value)) == 0)
		{
			tmp = cur->next->next;
			node = cur->next;
			gc_del_one(node->value, ENV);
			gc_del_one(node, ENV);
			cur->next = tmp;
			return (0);
		}
		cur = cur->next;
	}
	return (0);
}

int	unset(char **value, t_env **env)
{
	t_env	*tmp;
	size_t	i;

	if (!(value[1] || !(*env)))
		return (0);
	i = 0;
	while (value[++i])
	{
		if (value[i][0] == 0)
			return (print_without_exit \
				("Minishell: unset: `': not a valid identifier\n", RED, 1), 1);
		if (ft_strcmp(value[i], (*env)->value
				, (int)env_size((*env)->value)) == 0)
		{
			tmp = *env;
			if ((*env)->next)
				*env = (*env)->next;
			else
				*env = NULL;
			gc_del_one(tmp, ENV);
		}
		else
			search_and_unset(value, env, i);
	}
	return (0);
}
