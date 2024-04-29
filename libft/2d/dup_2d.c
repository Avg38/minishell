/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:12:01 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/29 15:12:02 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**dup_2d(char **tab)
{
	size_t	i;
	size_t	size;
	char	**dup;

	i = 0;
	size = len_2d(tab) + 1;
	dup = (char **)ft_calloc(size, sizeof(char *));
	if (!dup)
		return (NULL);
	while (i < size - 1)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (free_2d(dup), NULL);
		i++;
	}
	return (dup);
}
