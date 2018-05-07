/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:27:11 by arohani           #+#    #+#             */
/*   Updated: 2017/05/03 15:17:51 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*fresh;

	if (lst)
	{
		if (!(fresh = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		fresh = f(lst);
		start = fresh;
		while (lst->next)
		{
			if (!(fresh->next = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			lst = lst->next;
			fresh->next = f(lst);
			fresh = fresh->next;
		}
		return (start);
	}
	return (0);
}
