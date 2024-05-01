/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sei <sei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:51 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/01 20:10:59 by sei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	*env_get_name(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

t_env	*env_init(char **env_array)
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
		new->value = gc_strndup(env_array[i], ft_strlen(env_array[i]), ENV);
		if (!new->value)
			print_and_exit(ERR_MALLOC, RED, 1);
		new->next = NULL;
		new->secret = 0;
		env_add_back(&env, new);
		i++;
	}
	return (env);
}
