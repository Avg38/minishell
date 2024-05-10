/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:51:36 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/10 14:00:49 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_prompt(t_shell *shell)
{
	char	*home;
	char	*prompt;
	int		len_home;

	home = getenv("HOME");
	prompt = env_get_value(shell->env, "PWD", 3);
	if (!prompt)
		prompt = "Minishell";
	if (home && ft_strnstr(prompt, home, ft_strlen(home)))
	{
		len_home = ft_strlen(home);
		if (prompt[0] == '/' && prompt[1] == '/')
			len_home += 1;
		prompt[len_home - 1] = '~';
		prompt = &prompt[len_home - 1];
	}
	if (g_status == 0)
		prompt = gc_strjoin("\001\e[32;1m\002> \001\e[37m\002", prompt, TMP);
	else
		prompt = gc_strjoin("\001\e[32;1m\002> \001\e[37m\002", prompt, TMP);
	prompt = gc_strjoin(prompt, "$ \x1b[0m", TMP);
	if (!prompt)
		print_and_exit(ERR_MALLOC, RED, 1);
	return (prompt);
}
