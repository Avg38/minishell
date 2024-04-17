#include "../../include/minishell.h"

int	brackets_is_empty(char *content)
{
	size_t	i;

	i = 1;
	while (content[i] && content[i] != ')')
	{
		if (ft_isspace(content[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

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
	if (tkntype == IN || tkntype == OUT || tkntype == APPEND)
		return (1);
	return (0);
}

int	tkn_is_operator(t_tkntype tkntype)
{
	if (tkntype == PIPR || tkntype == AND || tkntype == OR)
		return (1);
	return (0);
}
