
#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void) ac;
	if (ac > 1)
		print_and_exit(MSG_ARGS_ERR, RED, 1);
	if (!envp[0])
		print_and_exit(MSG_UNAVAILABLE_ENV, RED, 1);
	shell.env = init_env(envp);
	shell.io_global = (t_io){0, 1};
	shell.last_gstatus = 0;
	singleton_shell(&shell);
	handle_shlvl(shell.env, 1);
	prompt_loop(&shell);
}
