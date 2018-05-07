/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:05:03 by arohani           #+#    #+#             */
/*   Updated: 2018/02/20 14:51:44 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
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
				chdir(tmp->val);
				update_old_pwd(shell, tmp->val);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: No home directory.\n", 2);
	return (0);
}

static void	grab_pwd(t_shell *shell, char **clean)
{
	t_env	*tmp = shell->list;

	//printf("entered grab_pwd\n");
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PWD") == 0 && tmp->val)
		{
			*clean = (tmp->val[ft_strlen(tmp->val) - 1] == '/') ?
				ft_strdup(tmp->val) : ft_strjoin(tmp->val, "/");
			return ;		
		}
		tmp = tmp->next;
	}
}

static void handle_dot_dots(t_shell *shell)
{
	char	**tab;
	int		i = 0;
	int		last = 0;
	int		deleted_match = 0;
	char	*clean = NULL;
	char	*tmp = NULL;

	//printf("entering handle_dot_dots\n");
	tab = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	clean = ft_strdup("/");
	while (tab && tab[i]) // to get end-of-table so that we can later work with table despite removing elements before end
		i++;
	last = i;
	i = 0;
	while (tab && i < last && i >= 0)
	{
		if (tab[i] && ft_strcmp(tab[i], "..") == 0)
		{
			deleted_match = 0;
			ft_strdel(&tab[i--]);
			while (i >= 0 && deleted_match == 0)
			{
				if (!(tab[i]) && i == 0)
				{
					ft_strdel(&ARG);
					cd_no_arg(shell);
					return ;
				}
				else if (tab[i])
				{
					ft_strdel(&tab[i]);
					deleted_match = 1;
				}
				else
					i--;
			}
		}
		i++;
	}
	i = 0;
	while (i < last)
	{
		if (tab[i])
		{
			tmp = ft_strjoin(clean, tab[i]);
			ft_strdel(&clean);
			ft_strdel(&tab[i]);
			clean = ft_strjoin(tmp, "/");
			ft_strdel(&tmp);
		}
		i++;
	}
	free(tab);
	if (clean[ft_strlen(clean) - 1] == '/')
		clean[ft_strlen(clean) - 1] = '\0';
	ft_strdel(&ARG);
	ARG = ft_strdup(clean);
	ft_strdel(&clean);
	//printf("exiting dot dot handler, fully-processed path = %s\n", ARG);
}

static void	cd_canon(t_shell *shell)
{
	//successfully removes single dots and shortens remaining string, now need to process .. and treat symbolic links
	char	*clean = NULL;
	char	*tmp = NULL;
	int		i = 0;
	char	**tab;

	tab = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if (ARG[0] != '/') //to concat with PWD if curpath doesnt start from root
		grab_pwd(shell, &clean);
	else
		clean = ft_strdup("/");	//to account for curpath starting from root
	while (tab && tab[i])
	{
		if (tab[i] && ft_strcmp(tab[i], "."))
		{
			if (!clean)
				clean = ft_strjoin(tab[i], "/");
			else if (clean && tab[i])
			{
				tmp = ft_strjoin(clean, tab[i]);
				ft_strdel(&clean);
				clean = (tab[i+1]) ? ft_strjoin(tmp, "/") : ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		i++;
	}
	free_table(tab);
	ft_strdel(&(ARG));
	ARG = ft_strdup(clean);
	ft_strdel(&clean);
	if (ft_strstr(ARG, ".."))
		handle_dot_dots(shell);
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
			{
				ft_putstr_fd("cd: not a directory: ", 2);
				ft_putendl_fd(tmp->val, 2);
			}
			else
			{
				ft_putendl(tmp->val);
				update_old_pwd(shell, tmp->val);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: OLDPWD not set\n", 2);
	return (1);
}

static int	cd_relative(t_shell *shell)
{
	t_env	*tmp;
	char	cwd[256];

	printf("entered cd_relative with %s\n", ARG);
	tmp = (shell->list) ? shell->list : NULL;
	if (chdir(ARG) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(ARG, 2);
		ft_putstr_fd(": No such file or directory\n", 2);		
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			ft_putstr_fd("error retrieving cwd\n", 2);
		else
			(shell->p == 1 && shell->l == 0) ? update_old_pwd(shell, cwd) : update_old_pwd(shell, ARG);
	}
	return (1);
}

int			regular_cd(t_shell *shell)
{
	char	cwd[256];	

	cd_canon(shell);
	if (chdir(ARG) != 0)
	{
	//	printf("first tried changing directory without concat of cdpath\nhas_paths(shell) = %d\n", has_paths(shell, 1));
		//include clause to check for CDPATH and concat, similar to execution of binaries searched via PATH
		if (has_paths(shell, 1) == 2 && cd_path(shell))
			return (1);
		else
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(ARG, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	else{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			ft_putstr_fd("error retrieving cwd\n", 2);
		else
			(shell->p == 1 && shell->l == 0) ? update_old_pwd(shell, cwd) : update_old_pwd(shell, ARG);
	}
	return (1);
}

int			ash_cd(t_shell *shell)
{
	shell->st = opt_check(shell);
	printf("shell->st = %d\nshell->l = %d\nshell->p = %d\n", shell->st, shell->l, shell->p);
	if (shell->st == -1)
		return (1);
	if (ARG == NULL && ft_strcmp(shell->args[shell->st - 1], "-") != 0)
		cd_no_arg(shell);
	else if (shell->args && (ft_strcmp(shell->args[shell->st - 1], "-") == 0))
		cd_dash(shell);
	else if (shell->args && ARG[0] == '.')
	{
		printf("before feeding cd args to cd_canon then cd_relative, ARG = %s\n", ARG);
		cd_canon(shell);
		printf("after cd_canon and before cd_relative, ARG = %s\n", ARG);
		cd_relative(shell);
	}
	else
		regular_cd(shell);
	return (1);
}
