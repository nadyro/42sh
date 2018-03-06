/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 13:52:51 by azybert           #+#    #+#             */
/*   Updated: 2017/01/30 18:35:46 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*first_node;
	t_list	*current_node;

	first_node = NULL;
	current_node = NULL;
	if (lst)
	{
		result = f(lst);
		if ((first_node = ft_lstnew(result->content, result->content_size)))
		{
			current_node = first_node;
			while ((lst = lst->next))
			{
				result = f(lst);
				if (!(current_node->next =
						ft_lstnew(result->content, result->content_size)))
					return (NULL);
				current_node = current_node->next;
			}
		}
	}
	return (first_node);
}
