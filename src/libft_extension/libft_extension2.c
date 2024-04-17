#include "../../include/minishell.h"

size_t	ft_strlen_utils(const char *str, int (*f)(char))
{
	size_t	len;

	len = 0;
	while (str[len] && !f(str[len]))
		len++;
	return (len);
}

size_t	ft_strlen_untils_char(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

size_t	ft_strlen_until_not(const char *str, int (*f)(char))
{
	size_t	len;

	len = 0;
	while (str[len] && f(str[len]))
		len++;
	return (len);
}

size_t	ft_strlen_until_not_char(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] == c)
		len++;
	return (len);
}

int	str_contains_all_subs_ordered(char *str, char **subs)
{
	ssize_t	i;
	size_t	sub;
	size_t	j;

	if (!str || !subs)
		return (0);
	if (!subs[0])
		return (1);
	i = -1;
	sub = 0;
	j = 0;
	while (str[++i])
	{
		if (subs[sub][j] != str[i])
			j = 0;
		j++;
		if (!subs[sub][j])
		{
			sub++;
			j = 0;
			if (!subs[sub])
				return (1);
		}
	}
	return (0);
}
