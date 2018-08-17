/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:05:03 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 17:58:59 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#define ARG shell->args[shell->st]

static int	cd_no_arg(t_shell *shell)
{
	t_env	*tmp;

	tmp = (shell->list->var) ? shell->list : NULL;
	while (tmp && !(ARG))
	{
		if (ft_strcmp(tmp->var, "HOME") == 0)
		{
			if (tmp->val)
			{
				if (chdir(tmp->val) != 0)
					return (cd_error_mgmt(tmp->val));
				update_old_pwd(shell, tmp->val);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: No home directory.\n", 2);
	return (-1);
}

static int	cd_dash(t_shell *shell)
{
	t_env		*tmp;

	tmp = (shell->list) ? shell->list : NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "OLDPWD") == 0)
		{
			if (chdir(tmp->val) != 0)
				return (cd_error_mgmt(tmp->val));
			else
			{
				ft_putendl(tmp->val);
				update_old_pwd(shell, tmp->val);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: OLDPWD not set\n", 2);
	return (-1);
}

int			regular_cd(t_shell *shell)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_putstr_fd("Error retrieving cwd\n", 2);
	else
	{
		(shell->p == 1 && shell->l == 0) ?
			update_old_pwd(shell, cwd) : update_old_pwd(shell, ARG);
		return (0);
	}
	return (-1);
}

int			ash_cd(t_shell *shell, int env)
{
	shell->st = cd_opt_check(shell);
	if (shell->st == -1)
		return (1);
	if (ARG == NULL && ft_strcmp(shell->args[shell->st - 1], "-") != 0)
		return (cd_no_arg(shell));
	else if (shell->args && (ft_strcmp(shell->args[shell->st - 1], "-") == 0))
		return (cd_dash(shell));
	else if (ARG)
	{
		if (ARG[0] != '/' && ARG[0] != '.')
		{
			if (has_paths(shell, 1, env) == 2)
				cd_path(shell, 0, fetch_cd_paths(shell));
		}
		if (chdir(ARG) != 0)
			return (cd_error_mgmt(ARG));
		cd_canon(shell);
		return (regular_cd(shell));
	}
	return (-1);
}
