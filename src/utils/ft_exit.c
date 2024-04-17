#include "../../include/minishell.h"

void	free_and_exit(int exit_code)
{
	rl_clear_history();
	gc_clear(TMP, free);
	gc_clear(ENV, free);
	gc_clear(B_TREE, free);
	exit(exit_code);
}

void	print_and_exit(char *msg, char *color, int exit_code)
{
	write(2, color, ft_strlen(color));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	write(2, RESET, ft_strlen(RESET));
	if (exit_code)
		free_and_exit(exit_code);
}

void	print_without_exit(char *msg, char *color, int exit_code)
{
	write(2, color, ft_strlen(color));
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
	g_status = exit_code;
}

void	print_path_error(char *arg, int exit_code, int error)
{
	ft_printf_fd(2, "Minishell: %s", arg);
	if (error == 1)
		ft_printf_fd(2, ": Permission denied");
	if (error == 2)
		ft_printf_fd(2, ": No such file or directory");
	if (error == 3)
		ft_printf_fd(2, ": Permission denied");
	if (error == 4)
		ft_printf_fd(2, ": is a directory");
	if (error == 5)
		ft_printf_fd(2, ERR_DOT);
	free_and_exit(exit_code);
}

void	print_str_error(char *arg, char *color, int new_status)
{
	write(2, color, ft_strlen(color));
	ft_printf_fd(2, "Minishell: ");
	if (arg)
		ft_printf_fd(2, "%s: ", arg);
	ft_printf_fd(2, "%s\n", str_error(errno));
	write(2, RESET, ft_strlen(RESET));
	g_status = new_status;
}