/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:18:11 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/08 14:04:56 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*gc_add(void *ptr, int gc_id)
{
	t_list	*element;

	if (gc_id < 0 || gc_id >= GC_SIZE)
		return (NULL);
	element = ft_lstnew(ptr);
	if (element == NULL)
		return (free(ptr), NULL);
	ft_lstadd_front(garbage_ptr(gc_id), element);
}
