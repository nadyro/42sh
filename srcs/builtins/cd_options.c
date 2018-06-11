/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:16:39 by arohani           #+#    #+#             */
/*   Updated: 2018/05/11 16:16:56 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	cd_fill_flags(t_shell *shell, int i)
{
	int			j;

	j = 1;
	while (shell->args[i][j])
	{
		if (shell->args[i][j] == 'P')
			shell->p = 1;
		else if (shell->args[i][j] == 'L')
			shell->l = 1;
		else
			return (i);
		j++;
	}
	return (0);
}

int			cd_opt_check(t_shell *shell)
{
	int			i;
	int			j;

	i = 1;
	j = 1;
	shell->p = 0;
	shell->l = 0;
	while (shell->args && shell->args[i])
	{
		if (!ft_strcmp(shell->args[i], "--"))
			return (i + 1);
		else if (shell->args[i][0] == '-')
		{
			if (cd_fill_flags(shell, i) != 0)
				return (i);
		}
		else
			return (i);
		j = 1;
		i++;
	}
	return (i);
}
