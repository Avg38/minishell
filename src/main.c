#include "../include/minishell.h"

/*
cette fonction sert a ....
*/

t_shell	*singleton_shell(t_shell *addr_shell)
{
	static t_shell	*shell_todeliver;

	if (addr_shell)
		shell_todeliver = addr_shell;
	return (shell_todeliver);
}

/*

*/

void	handle_shlvl(t_env *env, int nb)
{
	char	*shell_level;
	int		lvl;

	lvl = ft_atoi(get_env_value(env, "SHLVL", 5));
	if (lvl >= 999)
	{
		ft_printf_fd(2, ERR_SHLVL, lvl + 1);
		lvl = 1;
	}
	else if (lvl < 0)
		lvl = 0;
	else
		lvl += nb;
	shell_level = gc_itoa(lvl, ENV);
	if (!shell_level)
		print_and_exit(ERR_MALLOC, RED, 1);
	shell_level = gc_strjoin("SHLVL=", shell_level, TMP);
	if (!shell_level)
		print_and_exit(ERR_MALLOC, RED, 1);
	is_in_env(env, shell_level);
	rl_outstream = stderr; //???
}

/*
Voici le main.
*/

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void) ac;
	if (ac > 1)
		print_and_exit(ERR_ARGS, RED, 1);
	if (!envp[0])
		print_and_exit(ERR_UNAVAILABLE_ENV, RED, 1);
	shell.env = env_init(envp);
	shell.io_global = (t_io){0, 1};
	shell.last_gstatus = 0;
	singleton_shell(&shell);
	handle_shlvl(shell.env, 1);
	prompt_loop(&shell);
}
