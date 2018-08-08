/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:50:10 by arohani           #+#    #+#             */
/*   Updated: 2018/08/08 16:55:03 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#define ARG shell->args[shell->st]

static char	**fetch_paths(t_shell *shell)
{
	t_env	*tmp;
	char	**path;

	tmp = shell->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PATH") == 0)
		{
			path = ft_strsplit(tmp->val, ':');
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char	**fetch_cd_paths(t_shell *shell)
{
	char	**path = NULL;
	t_env	*tmp;

	tmp = shell->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "CDPATH") == 0)
		{
			path = ft_strsplit(tmp->val, ':');
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char		*arg_full_path(t_shell *shell)
{
	char		*str;
	char		*full_path;
	int			ret;
	int			i;
	char		**paths;

	i = 0;
	paths = fetch_paths(shell);
	while (paths && paths[i])
	{
		str = (paths[i][ft_strlen(paths[i]) - 1] != '/')
		? ft_strjoin(paths[i++], "/") : ft_strdup(paths[i++]);
		full_path = ft_strjoin(str, shell->args[0]);
		if (str && str[0])
			ft_strdel(&str);
		if (!(ret = access(full_path, F_OK)))
		{
			free_table(paths);
			return (full_path);
		}
		if (full_path && full_path[0])
			ft_strdel(&full_path);
	}
	if (paths)
		free_table(paths);
	return (NULL);
}

int		cd_path(t_shell *shell)
{
	// not accounting for cd path in modified environment. should verify if env -i can call builtins?
	char		*str;
	char		*full_path;
	char		**paths;
	int			i;
	int			ret;

	i = 0;
	paths = fetch_cd_paths(shell);
	//printf("about to print path after fetching from fetch_cd_paths\n");
	//ft_print_table(paths);
	while (paths && paths[i])
	{
		str = (paths[i][ft_strlen(paths[i]) - 1] != '/')
		? ft_strjoin(paths[i++], "/") : ft_strdup(paths[i++]);
	//	printf("about to join %s to %s\n", ARG, str);
		full_path = ft_strjoin(str, ARG);
		if (str && str[0])
			ft_strdel(&str);	
	//	printf("about to test full_path using access: full_path = %s\n", full_path);
		if (!(ret = access(full_path, F_OK)))
		{
			free_table(paths);
			ft_strdel(&(ARG));
			ARG = ft_strdup(full_path);
			ft_strdel(&full_path);
			//printf("cd_path located, ARG now = %s\n", ARG);
			//regular_cd(shell);
			return (1);
		}
		else if (full_path && full_path[0])
			ft_strdel(&full_path);
	}
	if (paths && paths[0])
		free_table(paths);
	return (0);
}

int			has_paths(t_shell *shell, int cdpath)
{
	t_env		*tmp;

	if (!(shell->list) || (shell->list && !(shell->list->var)))
		return (0);
	tmp = shell->list;
	while (tmp)
	{
		if (cdpath == 0 && ft_strcmp(tmp->var, "PATH") == 0)
			return (1);
		if (cdpath == 1 && ft_strcmp(tmp->var, "CDPATH") == 0)
		{
	//		printf("about to return 2 from has_paths\n");
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}
