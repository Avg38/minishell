#include "../../include/minishell.h"

/*
cette fonction est le manager des executions,
elle intervient lorsque l'on a un type WORD parmi
les commandes (LS, TEXTE ect..)
*/

// int	exec_handler(t_shell *shell, t_btree *node, t_io fds)
// {
// 	int		ret_status;
// 	bool	cmd_builtin;
// 	bool	pipe_is_present;

// 	ret_status = 0;
// 	cmd_builtin = is_builtin(node->cmds[0]);
// 	pipe_is_present = cmd_in_pipe(shell->btree, node->branch);
// 	if (pipe_is_present == true && cmd_builtin == true)
// 		ret_status = fork_builtin(&(shell->env), node, fds);
// 	else if (pipe_is_present == false && cmd_builtin == true)
// 		ret_status = exec_builtin(&(shell->env), node, fds);
// 	else
// 		ret_status = exec_bin(shell->env, node, fds);
// 	return (ret_status);
// }

int	exec_handler(t_shell *shell, t_btree *node, t_io fds)
{
	int		ret_status;
	bool	cmd_builtin;
	bool	pipe_is_present;

	ret_status = 0;
	cmd_builtin = is_builtin(node->cmds[0]);
	pipe_is_present = cmd_in_pipe(shell->btree, node->branch);
	if (pipe_is_present == true && cmd_builtin == true)
	{
		ft_printf("pipe is present : fork_builtin execution\n");
		ret_status = fork_builtin(&(shell->env), node, fds);
	}
	else if (pipe_is_present == false && cmd_builtin == true)
	{
		ft_printf("pipe is not present but cmd does : exec_builtin\n");
		ret_status = exec_builtin(&(shell->env), node, fds);
	}
	else
	{
		ft_printf("nothing special is present : exec_bin\n");
		ret_status = exec_bin(shell->env, node, fds);
	}
	return (ret_status);
}
