/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:17:29 by arohani           #+#    #+#             */
/*   Updated: 2018/07/19 17:23:58 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	display_setenv(t_shell *shell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->list;
	if (!(shell->args && shell->args[1]) && shell->envv)
	{
		ft_print_table(shell->envv);
		return (1);
	}
	else if (shell->args && shell->args[1] && shell->args[2] && shell->args[3])
	{
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
		return (1);
	}
	else if (shell->args && shell->args[1][i])
	{
		while (shell->args && shell->args[1][i])
			if (ft_isalnum(shell->args[1][i++]) == 0)
			{
				ft_putstr_fd("setenv: must use alphanumeric characters.\n", 2);
				return (1);
			}
	}
	return (0);
}

static void	add_to_env(t_shell *shell, t_env **tmp)
{
	t_env		*prev;

	prev = *tmp;
	if (*tmp && !((*tmp)->next))
	{
		if (!((*tmp)->next = (t_env *)malloc(sizeof(t_env))))
		{
			ft_putstr_fd("malloc error adding to env list with setenv\n", 2);
			return ;
		}
		*tmp = (*tmp)->next;
		(*tmp)->prev = prev;
		(*tmp)->var = (shell->args[1]) ? ft_strdup(shell->args[1]) : NULL;
		(*tmp)->val = (shell->args[2] && shell->args[2][0])
		? ft_strdup(shell->args[2]) : NULL;
		(*tmp)->next = NULL;
		if (shell->envv)
			free_table(shell->envv);
		shell->envv = env_to_tab(shell->list);
		return ;
	}
	ft_putstr_fd("error adding to env list using setenv\n", 2);
	return ;
}

static int	setenv_parse(t_shell *shell, t_env *tmp)
{
	while (tmp)
	{
		if (ft_strcmp(shell->args[1], tmp->var) == 0)
		{
			if (tmp->val)
				ft_strdel(&(tmp->val));
			tmp->val = (shell->args[2] && shell->args[2][0])
			? ft_strdup(shell->args[2]) : NULL;
			if (shell->envv)
				free_table(shell->envv);
			shell->envv = env_to_tab(shell->list);
			return (1);
		}
		if (!(tmp->next))
			add_to_env(shell, &tmp);
		tmp = tmp->next;
	}
	return (1);
}

int			ash_setenv(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->list;
	if (display_setenv(shell) == 1)
		return (1);
	else
		setenv_parse(shell, tmp);
	return (1);
}
