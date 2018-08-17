/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:50:10 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 12:54:25 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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

char		**fetch_cd_paths(t_shell *shell)
{
	char	**path;
	t_env	*tmp;

	path = NULL;
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
	full_path = NULL;
	paths = fetch_paths(shell);
	while (paths && paths[i])
	{
		str = (paths[i][ft_strlen(paths[i]) - 1] != '/')
			? ft_strjoin(paths[i++], "/") : ft_strdup(paths[i++]);
		full_path = ft_strjoin(str, shell->args[0]);
		if (str && str[0])
			ft_strdel(&str);
		if (!(ret = access(full_path, F_OK)))
			break ;
		else if (full_path && full_path[0])
			ft_strdel(&full_path);
	}
	if (paths)
		free_table(paths);
	return (full_path);
}

int			cd_path(t_shell *shell, int i, char **paths)
{
	char		*str;
	char		*full_path;

	while (paths && paths[i])
	{
		str = (paths[i][ft_strlen(paths[i]) - 1] != '/')
			? ft_strjoin(paths[i++], "/") : ft_strdup(paths[i++]);
		full_path = ft_strjoin(str, ARG);
		if (str && str[0])
			ft_strdel(&str);
		if (!(access(full_path, F_OK)))
		{
			free_table(paths);
			ft_strdel(&(ARG));
			ARG = ft_strdup(full_path);
			ft_strdel(&full_path);
			return (1);
		}
		else if (full_path && full_path[0])
			ft_strdel(&full_path);
	}
	if (paths && paths[0])
		free_table(paths);
	return (0);
}
#include <stdio.h>
int			has_paths(t_shell *shell, int cdpath, int env)
{
	t_env		*tmp;

	if (!(shell->list) || (shell->list && !(shell->list->var)))
		return (0);
	tmp = (env) ? shell->list->mod : shell->list;
	while (tmp)
	{
		if (cdpath == 0 && ft_strcmp(tmp->var, "PATH") == 0)
		{
			fprintf(stderr, "returning 1 from has_paths\n");
			return (1);
		}
		if (cdpath == 1 && ft_strcmp(tmp->var, "CDPATH") == 0)
		{
			fprintf(stderr, "returning 2 from has_paths\n");
			return (2);
		}
		tmp = tmp->next;
	}
	fprintf(stderr, "returning 0 from hast_paths\n");
	return (0);
}
