/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sei <sei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:12:33 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/01 18:06:40 by sei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*gc_strdup(const char *str, int gc_id)
{
	char	*result;
	size_t	length;

	length = ft_strlen(str);
	result = (char *)gc_malloc((length + 1) * sizeof(char), gc_id);
	if (!result)
		return (NULL);
	length = 0;
	while (str[length] != '\0')
	{
		result[length] = str[length];
		length++;
	}
	result[length] = '\0';
	return (result);
}
