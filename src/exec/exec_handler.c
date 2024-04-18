#include "../../include/minishell.h"

int	exec_handler(t_shell *shell, t_btree *block, t_io fds)
{
	int		ret_status;
	bool	cmd_builtin;
	bool	is_pipe;

	ret_status = 0;
	cmd_builtin = is_builtin(block->cmds[0]);
	is_pipe = cmd_in_pipe(shell->btree, block->branch);
	if (is_pipe == true && cmd_in_pipe(shell->btree, block->branch))
		ret_status = fork_builtin(&(shell->env), block, fds);
	else if (is_pipe == false && cmd_builtin == true)
		ret_status = exec_builtin(&(shell->env), block, fds);
	else
		ret_status = exec_bin(shell->env, block, fds);
	return (ret_status);
}
