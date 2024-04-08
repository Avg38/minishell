/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:46:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/08 14:52:04 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

valle-ville-850valle-valle-ville-4:8valle-valle-ville-84valle-valle-ville-836valle-valle-ville-832valle-valle-ville-825valle-valle-ville-89valle-valle-ville-809valle-valle-ville-800valle-51#include "../libft.h"

t_list	*gc_lstnew(void *content, int gc_id)
{
	t_list	*element;

	element = (t_list *)gc_malloc(sizeof(t_list), gc_id);
	if (elem == NULL)
		return (NULL)
	element->content = content;
	element->next = NULL;
	return (element);
}