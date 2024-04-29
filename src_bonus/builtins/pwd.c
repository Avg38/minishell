/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:43 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:15 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	pwd(t_io fds, t_env *env)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	cwd = env_get_value(env, "PWD", 3);
	if (cwd[0] == 0)
		cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	else
	{
		ft_putstr_fd(cwd, fds.fd_out);
		write(fds.fd_out, "\n", 1);
	}
	return (0);
}
