/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:50:00 by arohani           #+#    #+#             */
/*   Updated: 2018/07/28 17:19:03 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void		free_table(char **tabs)
{
	int		i;

	i = 0;
	if (tabs && !(tabs[0]))
	{
		//printf("about to free tab in free_table, address = %p\n", tab);
		free(tabs);
	}
	else
	{
		//printf("going to print all elements of the following table : \n");
		//ft_print_table(tab);
		while (tabs && tabs[i] != 0)
		{
		//	printf("about to free : %s, address = %p\n", tab[i], tab[i]);
			ft_strdel(&(tabs[i++]));
		}
		if (tabs != NULL)
		{
		//	printf("about to free tab after deleting all string elements, tab address = %p\n", tab);
			free(tabs);
		}
		tabs = NULL;
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
