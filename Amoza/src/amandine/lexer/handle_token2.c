#include "../../include/minishell.h"
/*
is_special_char sert a savoir si le caractere est un caractere speciale ou pas
*/
int	is_special_char(char c)
{
	return (c == ';' || c == '&' || c == '|' || c == '<' || c == '>');
}

int	handle_parenthese(char *buffer, t_tknlist *list)
{
	int	i;
	int	depth;

	i = 0;
	depth = 0;
	while (buffer[i])
	{
		if (buffer[i] == '(')
			depth++;
		else if (buffer[i] == ')')
		{
			depth--;
			if (depth == 0)
			{
				if (!add_node(list,
						create_node(PARENTHESE,
							ft_strndup(buffer, i + 1, TKN_LIST), 0)))
					print_and_exit(ERR_MALLOC, RED, 1);
				return (i + 1);
			}
		}
		i++;
	}
	return (handle_error_lexer(TKN_LIST, ERR_PARENTHESE));
}

int	handle_word(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 0;
	link = 0;
	while (buffer[i] != 0 && ft_isspace(buffer[i] == 0)
		&& is_operator(buffer[i], buffer[i + 1]) == 0)
	{
		if (buffer[i] == '\'' || buffer[i] == '\"'
			|| buffer[i] == '<' || buffer[i] == '>')
			break;
		i++;
	}
	if (!(buffer[i] == '<' || buffer[i] == '>')
		&& buffer[i] != 0 && ft_isspace(buffer[i]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(WORD, ft_strndup(buffer, i, TKN_LIST), link)))
		print_and_exit(ERR_MALLOC, RED, 1);
	return (i);
}

