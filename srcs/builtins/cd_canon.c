/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2018/07/26 18:06:32 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#define ARG shell->args[shell->st]

static void	grab_pwd(t_shell *shell, char **clean)
{
	t_env	*tmp = shell->list;

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

static int	cd_get_last(t_shell *shell, char ***split)
{
	int		dotdots = 0;
	int		i = 0;
	char	**tabs;
	
	tabs = *split;
	while (tabs && tabs[i])
	{
		//printf("in cd_get_last loop, tabs[i] = %s\n", tabs[i]);
		if (ft_strcmp(tabs[i], "..") == 0)
			dotdots++;
		i++;
	}
	//printf("after looping through table in cd_get_last, i = %d\ndotdots = %d\n", i, dotdots);
	if (dotdots >= ((i - 1)/2))
	{
	//	printf("too many dotdots, resetting operand to / in cd_get_last\n");
		ft_bzero(ARG, ft_strlen(ARG));
		ft_strcpy(ARG, "/");
		free_table(*split);
		return (-1);
	}
	//printf("about to return %d from cd_get_last", i);
	return (i);
}

static void handle_dot_dots(t_shell *shell)
{
	char	**tabs;
	int		i = 0;
	int		last = 0;
	int		deleted_match = 0;
	char	*clean = NULL;
	char	*tmp = NULL;

   // printf("at top of handle_dot_dots, ARG = %s\n", ARG);
	tabs = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if ((last = cd_get_last(shell, &tabs)) < 0)
		return ;
	clean = ft_strdup("/");
    //printf("cd canon 2 debug: i = %dlast = %d\n", i, last);
	while (tabs && i < last && i >= 0)
	{
      //  printf("top of cd canon 2 debug: i = %d\n", i);
		if (tabs[i] && ft_strcmp(tabs[i], "..") == 0)
		{
			deleted_match = 0;
			ft_strdel(&tabs[i--]);
        //    printf("cd_canon DEBUG : i = %d\n", i);
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
	i = 0;
	while (i < last)
	{
		if (tabs[i])
		{
			tmp = ft_strjoin(clean, tabs[i]);
			ft_strdel(&clean);
			ft_strdel(&tabs[i]);
			clean = ft_strjoin(tmp, "/");
			ft_strdel(&tmp);
		}
		i++;
	}
	free(tabs);
	if (clean[ft_strlen(clean) - 1] == '/')
		clean[ft_strlen(clean) - 1] = '\0';
	ft_strdel(&ARG);
	ARG = ft_strdup(clean);
	ft_strdel(&clean);
}

void	    cd_canon(t_shell *shell)
{
	char	*clean = NULL;
	char	*tmp = NULL;
	int		i = 0;
	char	**tabs;

	tabs = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if (ARG[0] != '/')
		grab_pwd(shell, &clean);
	else
		clean = ft_strdup("/");
	while (tabs && tabs[i])
	{
		if (tabs[i] && ft_strcmp(tabs[i], "."))
		{
			if (!clean)
				clean = ft_strjoin(tabs[i], "/");
			else if (clean && tabs[i])
			{
				tmp = ft_strjoin(clean, tabs[i]);
				ft_strdel(&clean);
				clean = (tabs[i+1]) ? ft_strjoin(tmp, "/") : ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		i++;
	}
	free_table(tabs);
	ft_strdel(&(ARG));
	ARG = ft_strdup(clean);
	ft_strdel(&clean);
	if (ft_strstr(ARG, ".."))
		handle_dot_dots(shell);
}
