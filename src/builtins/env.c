#include "../../include/minishell.h"

int	env(t_env *env, t_io fds)
{
	while (env)
	{
		if (env->secret == 0 && env->value != NULL)
		{
			ft_putstr_fd(env->value, fds.fd_out);
			wwrite(fds.fd_out, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
