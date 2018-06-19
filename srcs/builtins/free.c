/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:50:00 by arohani           #+#    #+#             */
/*   Updated: 2018/06/15 14:03:03 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		free_table(char **tab)
{
	int		i;

	i = 0;
	if (tab && !(tab[0]))
		free(tab);
	else
	{
		while (tab && tab[i] != 0)
			ft_strdel(&(tab[i++]));
		if (tab != NULL)
			free(tab);
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
