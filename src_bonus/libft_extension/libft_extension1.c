/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extension1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:50:23 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:23:23 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

char	*ft_strcut(char const *str, size_t cut_begin, size_t cut_end)
{
	char	*dest;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str) - cut_begin - cut_end;
	if (len <= 0)
		return (ft_strdup(""));
	dest = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &str[cut_begin], len + 1);
	dest[len] = 0;
	return (dest);
}

char	*replace_substr(char *str, char *replacement, size_t start, size_t len)
{
	char	*new;
	size_t	size_new;

	size_new = (ft_strlen(str) - len + ft_strlen(replacement)) + 1;
	new = (char *)ft_calloc(size_new, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, start);
	ft_strcat(new, replacement);
	ft_strcat(new, &str[start + len]);
	return (new);
}

char	*remove_substr(char *str, size_t start, size_t len_toremove)
{
	char	*new;
	size_t	size_new;

	size_new = ft_strlen(str) - len_toremove + 1;
	new = (char *)ft_calloc(size_new, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, start);
	ft_strcat(new, &str[start + len_toremove]);
	return (new);
}
