#include "../../include/minishell.h"

void	handle_signals_heredoc(char *input, size_t nb_lines, char *delim)
{
	if (!input)
	{
		if (g_status == 130)
			write(2, "\n", 1);
		else
			ft_printf_fd(2, ERR_HEREDOC, RED, (int)nb_lines, delim, RESET);
	}
}

int	readline_heredoc(t_btree *block, char *line \
	, size_t *nb_lines, int fd_pipe[2])
{
	if (ft_strlen(line) > 0 && ft_strcmp(line, block->cmds[0]) == 0)
		return (free(line), 1);
	ft_printf_fd(fd_pipe[FD_WRITE], "%s\n", line);
	free(line);
	(*nb_lines)++;
	return (0);
}

void	cross_heredoc(t_shell *shell, t_btree *block, t_io io_inherited)
{
	int		fd_pipe[2];
	char	*line;
	t_io	io_transmitted;
	size_t	nb_lines;

	ft_memcpy(&io_transmitted, &io_inherited, sizeof(t_io));
	if (pipe(fd_pipe) == -1)
		print_and_exit("Minishell: pipe error\n", RED, 1);
	line = readlin("> ");
	nb_lines = 1;
	while (line)
	{
		if (readline_heredoc(block, line, &nb_lines, fd_pipe) == 1)
			break;
		line = readline("> ");
	}
	handle_signals_heredoc(line, nb_lines, block->cmds[0]);
	close(fd_pipe[FD_WRITE]);
	if(io_inherited.fd_in != 0)
		close(io_inherited.fd_in);
	io_transmitted.fd_in = fd_pipe[FD_READ];
	browse_tree(shell, block->left, io_transmitted);
	close(fd_pipe[FD_READ]);
}
