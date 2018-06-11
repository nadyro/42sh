/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:00:58 by arohani           #+#    #+#             */
/*   Updated: 2018/02/21 17:55:24 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_mod_2(t_shell *shell, t_env **tail, int k)
{
	t_env	*prev;
	char	**av;
	char	*chr;

	chr = ft_strchr(shell->args[k], '=');
	av = ft_strsplit(shell->args[k], '=');
	prev = *tail;
	if (!((*tail)->next = (t_env *)malloc(sizeof(t_env))))
		return ;
	*tail = (*tail)->next;
	(*tail)->prev = prev;
	(*tail)->var = ft_strdup(av[0]);
	(*tail)->val = (av[1]) ? ft_strdup(chr + 1) : NULL;
	while ((chr = ft_strchr(shell->args[k], '=')))
		*chr = '&';
	(*tail)->next = NULL;
	if (av && av[0])
		free_table(av);
}

void		add_to_mod(t_shell *shell)
{
	int		k;
	t_env	*tail;
	t_env	*tmp;
	char	*chr;

	k = 1;
	tmp = shell->list->mod;
	while (tmp->next)
		tmp = tmp->next;
	tail = (tmp) ? tmp : NULL;
	while (tail && k < shell->list->last && shell->args[k])
	{
		while (shell->args[k] && !(ft_strchr(shell->args[k], '=')))
			k++;
		if (k < shell->list->last && shell->args[k] &&
			(chr = ft_strchr(shell->args[k], '=')))
		{
			add_to_mod_2(shell, &tail, k);
			k++;
		}
	}
}
