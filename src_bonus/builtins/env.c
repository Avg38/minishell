/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:27 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:13 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	env(t_env *env, t_io fds)
{
	while (env)
	{
		if (env->secret == 0 && env->value != NULL)
		{
			ft_putstr_fd(env->value, fds.fd_out);
			write(fds.fd_out, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
