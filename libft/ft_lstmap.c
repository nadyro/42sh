/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 23:06:22 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 16:06:48 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *node_lst;
	t_list *container_nl;

	if (lst != NULL)
	{
		if (!(node_lst = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		node_lst = f(lst);
		container_nl = node_lst;
		while (lst->next)
		{
			if (!(node_lst->next = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			lst = lst->next;
			node_lst->next = f(lst);
			node_lst = node_lst->next;
		}
		return (container_nl);
	}
	return (NULL);
}
