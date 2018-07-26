/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:50:00 by arohani           #+#    #+#             */
/*   Updated: 2018/07/26 18:06:12 by nsehnoun         ###   ########.fr       */
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
		//printf("about to free tabs in free_table, address = %p\n", tabs);
		free(tabs);
	}
	else
	{
		//printf("going to print all elements of the following table : \n");
		//ft_print_table(tabs);
		while (tabs && tabs[i] != 0)
		{
		//	printf("about to free : %s, address = %p\n", tabs[i], tabs[i]);
			ft_strdel(&(tabs[i++]));
		}
		if (tabs != NULL)
		{
		//	printf("about to free tabs after deleting all string elements, tabs address = %p\n", tabs);
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
