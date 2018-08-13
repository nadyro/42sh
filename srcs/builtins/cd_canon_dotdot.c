/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canon_dotdot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 16:36:38 by arohani           #+#    #+#             */
/*   Updated: 2018/08/13 16:54:46 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#define ARG shell->args[shell->st]

static void	remove_dotdots(char **tabs, int i, int last)
{
	int		deleted_match;

	deleted_match = 0;
	while (tabs && i < last && i >= 0)
	{
		if (tabs[i] && ft_strcmp(tabs[i], "..") == 0)
		{
			deleted_match = 0;
			ft_strdel(&tabs[i--]);
			while (i >= 0 && deleted_match == 0)
			{
				if (tabs[i])
				{
					ft_strdel(&tabs[i]);
					deleted_match = 1;
				}
				else if (deleted_match == 0)
					i--;
			}
		}
		i++;
	}
}

static void	replace_dotdots(char **tabs, char **clean, int i)
{
	char	*tmp;

	tmp = NULL;
	if (tabs[i])
	{
		tmp = ft_strjoin(*clean, tabs[i]);
		free(*clean);
		ft_strdel(&tabs[i]);
		*clean = ft_strjoin(tmp, "/");
		ft_strdel(&tmp);
	}
}

void		handle_dot_dots(t_shell *shell)
{
	char	**tabs;
	int		i;
	int		last;
	char	*clean;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tabs = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if ((last = cd_get_last(shell, &tabs)) < 0)
		return ;
	clean = ft_strdup("/");
	remove_dotdots(tabs, i, last);
	while (i < last)
	{
		replace_dotdots(tabs, &clean, i);
		i++;
	}
	free(tabs);
	if (clean[ft_strlen(clean) - 1] == '/')
		clean[ft_strlen(clean) - 1] = '\0';
	ft_strdel(&ARG);
	ARG = ft_strdup(clean);
	ft_strdel(&clean);
}
