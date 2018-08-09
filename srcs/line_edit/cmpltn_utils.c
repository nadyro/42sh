/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmpltn_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:45:18 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/09 09:40:04 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

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

void	send_nudes(t_node **my_phone)
{
	t_node	*nudes;

	nudes = *my_phone;
	while (nudes)
	{
		ft_putendl(nudes->cmd);
		nudes = nudes->next;
	}
}

void	free_lists(t_node *lst)
{
	t_node	*binaries_1;
	t_node	*tmp;

	binaries_1 = lst;
	while (binaries_1)
	{
		tmp = binaries_1->next;
		free(binaries_1->cmd);
		free(binaries_1);
		binaries_1 = tmp;
	}
	binaries_1 = NULL;
	lst = NULL;
}

void	print_nudes(t_node *matches)
{
	if (matches)
	{
		while (matches->prev != NULL)
			matches = matches->prev;
		send_nudes(&matches);
		while (matches->prev != NULL)
			matches = matches->prev;
		free_lists(matches);
	}
}

int		is_pre_binary(char c)
{
	if (c == '&' ||c == '|' ||c == '>' ||c == '<')
		return (1);
	return (0);
}
