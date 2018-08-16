/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:17:29 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 10:14:12 by arohani          ###   ########.fr       */
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
		return (0);
	}
	else if (shell->args && shell->args[1] && shell->args[2] && shell->args[3])
	{
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
		return (-1);
	}
	else if (shell->args && shell->args[1][i])
	{
		while (shell->args && shell->args[1][i])
			if (ft_isalnum(shell->args[1][i++]) == 0)
			{
				ft_putstr_fd("setenv: Must use alphanumeric characters.\n", 2);
				return (-1);
			}
	}
	return (1);
}

static int	add_to_env(t_shell *shell, t_env **tmp)
{
	t_env		*prev;

	prev = *tmp;
	if (*tmp && !((*tmp)->next))
	{
		if (!((*tmp)->next = (t_env *)malloc(sizeof(t_env))))
			return (-1);
		*tmp = (*tmp)->next;
		(*tmp)->prev = prev;
		(*tmp)->var = (shell->args[1]) ? ft_strdup(shell->args[1]) : NULL;
		(*tmp)->val = (shell->args[2] && shell->args[2][0])
		? ft_strdup(shell->args[2]) : NULL;
		(*tmp)->next = NULL;
		if (shell->envv)
			free_table(shell->envv);
		shell->envv = env_to_tab(shell->list);
		return (0);
	}
	ft_putstr_fd("Error adding to list of environment variables.\n", 2);
	return (-1);
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
			return (0);
		}
		if (!(tmp->next))
			if (add_to_env(shell, &tmp) == -1)
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int			ash_setenv(t_shell *shell)
{
	t_env	*tmp;
	int		ret;

	tmp = shell->list;
	if ((ret = display_setenv(shell)) == 1)
		return (setenv_parse(shell, tmp));
	return (ret);
}
