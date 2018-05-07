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
				update_old_pwd(shell, tmp->val);
				chdir(tmp->val);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("cd: No home directory.\n", 2);
	return (0);
}

static int	cd_dash(t_shell *shell)
{
	t_env		*tmp;
	struct stat	buf;

	tmp = (shell->list) ? shell->list : NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "OLDPWD") == 0)
		{
			if (lstat(tmp->val, &buf) >= 0)
			{
				if (chdir(tmp->val) != 0)
				{
					ft_putstr_fd("cd: not a directory: ", 2);
					ft_putendl_fd(tmp->val, 2);
				}
				else
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
			update_old_pwd(shell, cwd);
	}
	return (1);
}

int			regular_cd(t_shell *shell)
{
	struct stat	buf;

	if (lstat(ARG, &buf) >= 0)
	{
		if ((S_ISDIR(buf.st_mode)))
		{
			printf("%s is a directory\n", ARG);
			update_old_pwd(shell, ARG);
		}
		else if (!(S_ISLNK(buf.st_mode)))
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(ARG, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			return (1);
		}
	}
	if (chdir(ARG) != 0)
	{
	//	printf("first tried changing directory without concat of cdpath\nhas_paths(shell) = %d\n", has_paths(shell, 1));
		//include clause to check for CDPATH and concat, similar to execution of binaries searched via PATH
		if (has_paths(shell, 1) == 2 && cd_path(shell))
			return (1);
		else
		{
			if (lstat(ARG, &buf) >= 0 && S_ISLNK(buf.st_mode))
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(ARG, 2);
				ft_putstr_fd(": Too many levels of symbolic links\n", 2);
			}
			else
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(ARG, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
		}
	}
	return (1);
}

static void	grab_pwd(t_shell *shell, char **clean)
{
	t_env	*tmp = shell->list;

	printf("entered grab_pwd\n");
	while (tmp)
	{
		printf("DEBUG 1\n");
		if (ft_strcmp(tmp->var, "PWD") == 0 && tmp->val)
		{
			printf("DEBUG 2\n");
			*clean = (tmp->val[ft_strlen(tmp->val) - 1] == '/') ?
				ft_strdup(tmp->val) : ft_strjoin(tmp->val, "/");
			printf("DEBUG 3 in grab_pwd\nWAS: %s\nNOW: %s\n", shell->args[shell->st], *clean);
			return ;		
		}
		printf("DEBUG 4\n");
		tmp = tmp->next;
	}
	printf("DEBUG 5\n");
}

static void	cd_canon(t_shell *shell)
{
	//successfully removes single dots and shortens remaining string, now need to process .. and treat symbolic links
	char	*clean = NULL;
	char	*tmp = NULL;
	int		i = 0;
	char	**tab;

	tab = (shell->st > -1) ? ft_strsplit(shell->args[shell->st], '/') : NULL;
	printf("table after ft_strsplit is :\n");
	ft_print_table(tab);
	if (shell->args[shell->st][0] != '/') //to concat with PWD if curpath doesnt start from root
		grab_pwd(shell, &clean);
	else
		clean = ft_strdup("/");	//to account for curpath starting from root
	printf("DEBUG a\n");
	while (tab && tab[i])
	{
		if (tab[i] && ft_strcmp(tab[i], "."))
		{
			printf("DEBUG d, tab[i] = %s\n", tab[i]);
			if (!clean)
				clean = ft_strjoin(tab[i], "/");
			else if (clean && tab[i])
			{
				printf("DEBUG e\n");
				tmp = ft_strjoin(clean, tab[i]);
				printf("DEBUG f\n");
				ft_strdel(&clean);
				printf("DEBUG g\n");
				clean = ft_strjoin(tmp, "/");
				printf("DEBUG h\n");
				ft_strdel(&tmp);
				printf("DEBUG i\n");
			}
			printf("DEBUG j\n");
		}
		i++;
	}
	printf("DEBUG k\n");
	free_table(tab);
	printf("WAS: %s\nNOW: %s\n", shell->args[shell->st], clean);
	ft_strdel(&clean);
	printf("DEBUG l\n");
}

int			ash_cd(t_shell *shell)
{
	shell->st = opt_check(shell);
	cd_canon(shell);
	printf("shell->st = %d\nshell->l = %d\nshell->p = %d\n", shell->st, shell->l, shell->p);
	if (shell->st == -1)
		return (1);
	if (ARG == NULL)
		cd_no_arg(shell);
	else if (shell->args && (ft_strcmp(ARG, "-") == 0))
		cd_dash(shell);
	else if (shell->args && ARG[0] == '.')
		cd_relative(shell);
	else
		regular_cd(shell);
	return (1);
}
