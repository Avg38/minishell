/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:56 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 14:00:49 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	env_strlen(t_env *env)
{
	size_t	len;

	len = 0;
	if (env)
	{
		while (env)
		{
			len++;
			env = env->next;
		}
	}
	return (len);
}

char	*env_get_value(t_env *env, const char *var, size_t len)
{
	char	*path;

	while (env != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			path = gc_strdup(&env->value[len + 1], TMP);
			if (!path)
				print_and_exit(ERR_MALLOC, RED, 1);
			return (path);
		}
		env = env->next;
	}
	return ("");
}

size_t	size_all_value(t_env *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		if (lst->value != NULL)
		{
			len += ft_strlen(lst->value);
			len += 1;
		}
		lst = lst->next;
	}
	return (len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = (char *)malloc((size_all_value(lst) + 1) * sizeof(char));
	if (!env)
		print_and_exit(ERR_MALLOC, RED, 1);
	i = 0;
	while (lst)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j++];
				i++;
			}
		}
		if (lst->next)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = 0;
	return (env);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[PATH_MAX];
	char	env_name[PATH_MAX];

	env_get_name(var_name, args);
	while (env)
	{
		env_get_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			gc_del_one(env->value, ENV);
			env->value = gc_strndup(args, ft_strlen(args), ENV);
			if (!env->value)
				print_and_exit(ERR_MALLOC, RED, 1);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
