/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:17:43 by arohani           #+#    #+#             */
/*   Updated: 2018/08/14 18:04:40 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	unsetenv_swap(t_shell *shell, t_env **tmp, int *swap)
{
	t_env		*prev;
	t_env		*next;

	if ((*tmp)->var && (*tmp)->var[0])
		ft_strdel(&((*tmp)->var));
	if ((*tmp)->val && (*tmp)->val[0])
		ft_strdel(&((*tmp)->val));
	prev = (*tmp)->prev;
	next = (*tmp)->next;
	shell->list = (!prev && next) ? next : shell->list;
	if ((*tmp))
		free((*tmp));
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (!prev && next)
	{
		shell->list = next;
		(*tmp) = shell->list;
	}
	*swap = 1;
}

static void	unsetenv_parse(t_shell *shell, t_env *tmp, int *k, int *swap)
{
	while (tmp && shell->args && shell->args[*k])
	{
		while (shell->args && shell->args[*k] && tmp && *swap == 0)
		{
			if (ft_strcmp(shell->args[*k], "_") == 0 && *k)
			{
				if (shell->args[*k + 1])
					(*k)++;
				else
					return ;
			}
			if (ft_strcmp(shell->args[*k], tmp->var) == 0)
				unsetenv_swap(shell, &tmp, swap);
			else if (tmp)
				tmp = tmp->next;
		}
		(*k)++;
		tmp = shell->list;
		*swap = 0;
	}
}

int			ash_unsetenv(t_shell *shell)
{
	t_env	*tmp;
	int		k;
	int		swap;

	k = 1;
	swap = 0;
	tmp = shell->list;
	if (!(shell->args && shell->args[1]))
	{	
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
		return (-1);
	}
	unsetenv_parse(shell, tmp, &k, &swap);
	if (k > 1 && shell->envv)
	{
		if (shell->envv && shell->envv[0])
			free_table(shell->envv);
		shell->envv = (shell->list) ? env_to_tab(shell->list) : NULL;
	}
	return (0);
}
