/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 16:57:24 by arohani           #+#    #+#             */
/*   Updated: 2018/08/13 16:58:03 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		free_table(char **tabs)
{
	int		i;

	i = 0;
	if (tabs && !(tabs[0]))
		free(tabs);
	else
	{
		while (tabs && tabs[i] != 0)
		{
			ft_strdel(&(tabs[i++]));
		}
		if (tabs != NULL)
			free(tabs);
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
