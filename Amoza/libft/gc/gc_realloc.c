/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:06:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/08 14:06:24 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*gc_realloc(void *ptr, size_t old_size, size_t new_size, int id_gc)
{
	size_t	size;
	void	*new;

	if (new_size == 0)
		return (del_one_garbage(ptr, id_gc), NULL);
	size = (size_t)max_value_size_t(old_size, new_size);
	new = gc_malloc(new, ptr, size);
	if (ptr)
		ft_memcpy(new, ptr, size);
}
