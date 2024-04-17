#include "../../include/minishell.h"

int	tkn_is_logic(t_tkntype tkntype)
{
	if (tkntype == AND || tkntype == OR)
		return (1);
	return (0);
}

int	tkn_is_cmd(t_tkntype tkntype)
{
	if (tkntype == WORD || tkntype == S_QUOTE || tkntype == D_QUOTE)
		return (1);
	return (0);
}

int	tkn_is_redir(t_tkntype tkntype)
{
	if (tkntype == AND || tkntype == OR)
		return (1);
	return (0);
}

int	tkn_is_operator(t_tkntype tkntype)
{
	if (tkntype == AND || tkntype == OR)
		return (1);
	return (0);
}
