/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:50:10 by arohani           #+#    #+#             */
/*   Updated: 2018/02/21 13:14:35 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

	printf("entered cd_path\n");
	i = 0;
	printf("DEBUG 1\n");
	paths = fetch_cd_paths(shell);
	printf("DEBUG 2\n");
	while (paths && paths[i])
	{
		printf("DEBUG 3\n");
		str = (paths[i][ft_strlen(paths[i]) - 1] != '/')
		? ft_strjoin(paths[i++], "/") : ft_strdup(paths[i++]);
		//will eventually need to know starting point i.e. cd argument (different if there are options,
		//and depends on syntax) before concatenating str with cd argument
		printf("DEBUG 4\n");
		full_path = ft_strjoin(str, shell->args[1]);
		printf("DEBUG 5\n");
		if (str && str[0])
			ft_strdel(&str);
		printf("DEBUG 6\n");	
		if (!(ret = access(full_path, F_OK)))
		{
			printf("DEBUG 7\n");
			free_table(paths);
			printf("DEBUG 8\n");
			ft_strdel(&(shell->args[1]));
			printf("DEBUG 9\n");
			shell->args[1] = ft_strdup(full_path);
			printf("DEBUG 10\n");
			ft_strdel(&full_path);
			printf("DEBUG 11\n");
			regular_cd(shell);
			return (1);
			printf("DEBUG 12\n");
		}
		else if (full_path && full_path[0])
			ft_strdel(&full_path);
		printf("DEBUG 13\n");	
	}
	printf("DEBUG 14\n");
	if (paths && paths[0])
		free_table(paths);
	printf("DEBUG 15\n");
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
			printf("has paths will return 2\n");
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}
