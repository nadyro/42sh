/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:50:00 by arohani           #+#    #+#             */
/*   Updated: 2018/07/18 17:13:57 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void		free_table(char **tab)
{
	int		i;

	i = 0;
	if (tab && !(tab[0]))
	{
		//printf("about to free tab in free_table, address = %p\n", tab);
		free(tab);
	}
	else
	{
		//printf("going to print all elements of the following table : \n");
		//ft_print_table(tab);
		while (tab && tab[i] != 0)
		{
		//	printf("about to free : %s, address = %p\n", tab[i], tab[i]);
			ft_strdel(&(tab[i++]));
		}
		if (tab != NULL)
		{
		//	printf("about to free tab after deleting all string elements, tab address = %p\n", tab);
			free(tab);
		}
		tab = NULL;
	}
}

void		free_env(t_env *list)
{
	t_env	*next;
	t_env	*tmp;

	next = NULL;
	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->var && tmp->var[0])
			ft_strdel(&(tmp->var));
		if (tmp->val && tmp->val[0])
			ft_strdel(&(tmp->val));
		if (tmp)
			free(tmp);
		tmp = next;
	}
	tmp = NULL;
}
