#include "../../include/minishell.h"

int	wait_child(pid_t pid)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

void	browse_tree(t_shell *shell, t_btree *bloc, t_io io_inherited)
{
	if (!bloc || g_status == 130)
		return ;
	if (tkn_is_logic(bloc->type))
		cross_logic(shell, bloc, io_inherited);
	else if (bloc->type == PIPE)
		cross_pipe(shell, bloc, io_inherited)
	else if (bloc->type == IN)
		cross_input(shell, bloc, io_inherited)
	else if (bloc->type == OUT || bloc->type == APPEND)
		cross_output(shell, bloc, io_inherited)
	else if (bloc->type == HEREDOC)
		cross_heredoc(shell, bloc, io_inherited)
	else if (bloc->type == PARENTHESE)
		g_status = cross_brackets(shell, bloc, io_inherited)
	else if (bloc->type == WORD)
		g_status = exec_handler(shell, bloc, io_inherited)
}