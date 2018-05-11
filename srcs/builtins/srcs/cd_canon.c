/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2018/05/09 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

static void handle_dot_dots(t_shell *shell)
{
	char	**tab;
	int		i = 0;
	int		last = 0;
	int		deleted_match = 0;
	char	*clean = NULL;
	char	*tmp = NULL;

    printf("at top of handle_dot_dots, ARG = %s\n", ARG);
	tab = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	clean = ft_strdup("/");
	while (tab && tab[i])
		i++;
	last = i;
	i = 0;
    printf("cd canon 2 debug: i = %dlast = %d\n", i, last);
	while (tab && i < last && i >= 0)
	{
        printf("top of cd canon 2 debug: i = %d\n", i);
		if (tab[i] && ft_strcmp(tab[i], "..") == 0)
		{
			deleted_match = 0;
			ft_strdel(&tab[i--]);
            printf("cd_canon DEBUG : i = %d\n", i);
			while (i >= 0 && deleted_match == 0)
			{
                if (tab[i])
                {
                    ft_strdel(&tab[i]);
                    deleted_match = (i == 0) ? 0 : 1; //if we delete last match, set operand to '/' therefore dont set del_match to 1 and end loop
                }
				if (i == 0)
				{
                    printf("before deleting ARG in cd_canon, ARG = %s\n", ARG);
					ft_strdel(&ARG);
                    ARG = ft_strdup("/");
				//	cd_no_arg(shell); 
					return ;
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
}

void	    cd_canon(t_shell *shell)
{
	char	*clean = NULL;
	char	*tmp = NULL;
	int		i = 0;
	char	**tab;

	tab = (shell->st > -1) ? ft_strsplit(ARG, '/') : NULL;
	if (ARG[0] != '/')
		grab_pwd(shell, &clean);
	else
		clean = ft_strdup("/");
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