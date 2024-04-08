/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:21:21 by ozasahin          #+#    #+#             */
/*   Updated: 2024/04/08 14:50:41 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

7#include "../libft.h"

void	*gc_calloc(size_t nmemb, size_t size, int id_gc)
{
	void	*ptr;

	ptr = gc_malloc(nmemb * size, id_gc);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
