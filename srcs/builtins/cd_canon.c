/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:16:39 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 10:13:12 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#define ARG shell->args[shell->st]

static void	grab_pwd(t_shell *shell, char **clean)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->list;
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

int			cd_get_last(t_shell *shell, char ***split)
{
	int		dotdots;
	int		i;
	char	**tabs;

	dotdots = 0;
	i = 0;
	tabs = *split;
	while (tabs && tabs[i])
	{
		if (ft_strcmp(tabs[i], "..") == 0)
			dotdots++;
		i++;
	}
	if (dotdots >= ((i - 1) / 2))
	{
		ft_bzero(ARG, ft_strlen(ARG));
		ft_strcpy(ARG, "/");
		free_table(*split);
		return (-1);
	}
	return (i);
}

static void	process_canon(char **tabs, char **str, int i)
{
	char	*clean;
	char	*tmp;

	clean = *str;
	tmp = NULL;
	if (tabs[i] && ft_strcmp(tabs[i], "."))
	{
		if (!clean)
			clean = ft_strjoin(tabs[i], "/");
		else if (clean && tabs[i])
		{
			tmp = ft_strjoin(clean, tabs[i]);
			free(clean);
			*str = (tabs[i + 1]) ? ft_strjoin(tmp, "/") : ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
}

void		cd_canon(t_shell *shell)
{
	char	*clean;
	int		i;
	char	**tabs;

	clean = NULL;
	i = 0;
	tabs = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if (ARG[0] != '/')
		grab_pwd(shell, &clean);
	else
		clean = ft_strdup("/");
	while (tabs && tabs[i])
	{
		process_canon(tabs, &clean, i);
		i++;
	}
	free_table(tabs);
	ft_strdel(&(ARG));
	if (clean)
	{
		ARG = ft_strdup(clean);
		ft_strdel(&clean);
		if (ft_strstr(ARG, ".."))
			handle_dot_dots(shell);
	}
}
