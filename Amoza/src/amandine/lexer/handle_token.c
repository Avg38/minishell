#include "../../include/minishell.h"

int	handle_file(char *buffer, t_tknlist *list, t_tkntype type)
{
	int	i;

	if (type == APPEND || type == HEREDOC)
		i = 2;
	else
		i = 1;
	if (!add_node(list, create_node(type, ft_strndp(buffer, i, TKN_LIST), 1)))
		print_and_exit(MSG_MALLOC_ERR)
}