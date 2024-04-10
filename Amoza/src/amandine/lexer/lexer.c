#include "../../include/minishell.h"

t_tknlist	*lexer(char *buffer)
{
	int			i;
	t_tkntype	type;
	t_tknlist	list;

	if (!buffer || g_status != 0 || is_only_space(buffer) == 1)
		return (NULL);
	init_list(&list);
	i = 0;
	while (buffer[i])
	{
		if (is_space(buffer[i]))
		{
			if (detect_error_type(buffer[i]) == 1)
				break;
			type = detect_type(buffer[i], buffer[i + 1]);
			handle_token(&buffer[i], list, type, &i);
			if (g_status != 0)
				break;
		}
		else
			i++;
	}
	return (list);
}