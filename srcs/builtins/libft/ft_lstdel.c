/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:04:09 by arohani           #+#    #+#             */
/*   Updated: 2017/05/02 18:16:47 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*elem;
	t_list	*next_elem;

	elem = *alst;
	while (elem)
	{
		next_elem = elem->next;
		del(elem->content, elem->content_size);
		free(elem);
		elem = next_elem;
	}
	*alst = NULL;
}
