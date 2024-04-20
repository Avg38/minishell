#include "../../include/minishell.h"
/*
ft_strndup sert a allouer de la memoire
(dans le garbage collector) pour chaque "mot" de la commande
*/
char	*ft_strndup(char *buffer, int len, t_gc_id id)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = gc_malloc((i + 1) * sizeof(char), id);
	if (!new)
		print_and_exit(ERR_MALLOC, RED, 1);
	i = 0;
	while (buffer[i] && i < len)
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

/*
is_operator sert a savoir si le "mot" est un operateur ou pas
*/

int	is_operator(const char c1, const char c2)
{
	if (c1 == '|' && c2 != '|')
		return (1);
	else if (c1 == '&' && c2 == '&')
		return (1);
	else if (c1 == '|' && c2 == '|')
		return (1);
	return (0);
}

/*
detect_error_type sert a detecter les erreurs de type 
*/

int	detect_error_type(const char c)
{
	if (c == '(' || c == ';' || c == '\\')
		return (handle_error_lexer(TKN_LIST, ERR_WRONG_CHAR));
	return (0);
}
