/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmpltn_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:45:18 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/21 13:16:28 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

void	clean_tabs(char **t, int j)
{
	int		i;

	i = 0;
	while (t[i])
		ft_strclr(t[i++]);
	i = 0;
	while (t[i])
		ft_strdel(&t[i++]);
	if (j == 0)
		free(t);
}

void	send_nudes(t_list **my_phone)
{
	t_list	*nudes;

	nudes = *my_phone;
	while (nudes)
	{
		ft_putendl(nudes->content);
		nudes = nudes->next;
	}
}

void	free_lists(t_list *lst)
{
	t_list	*binaries_1;
	t_list	*tmp;

	binaries_1 = lst;
	while (binaries_1)
	{
		tmp = binaries_1->next;
		free(binaries_1->content);
		free(binaries_1);
		binaries_1 = tmp;
	}
	binaries_1 = NULL;
	lst = NULL;
}

void	print_nudes(t_list *matches)
{
	if (matches)
	{
		while (matches->previous != NULL)
			matches = matches->previous;
		send_nudes(&matches);
		while (matches->previous != NULL)
			matches = matches->previous;
		free_lists(matches);
	}
}
