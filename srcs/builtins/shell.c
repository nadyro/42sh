/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:47:36 by arohani           #+#    #+#             */
/*   Updated: 2018/07/29 16:27:12 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

static int	semicol_loop(t_shell *shell, char *line)
{
	int		status;
	int		i;
	char	**multi;

	multi = ft_strsplit(line, ';');
	i = 0;
	while (multi && multi[i])
	{
		shell->args = (multi[i]) ? ft_split_whitespaces(multi[i]) : NULL;
		status = ash_execute(shell);
		if (shell->args)
			free_table(shell->args);
		i++;
	}
	free_table(multi);
	return (status);
}

static int	no_semi_loop(t_shell *shell, char *line)
{
	int		status;

	shell->args = (line) ? ft_split_whitespaces(line) : NULL;
	status = ash_execute(shell);
	if (shell->args)
		free_table(shell->args);
	return (status);
}

static int	cmd_d(int ret, t_shell *shell)
{
	if (ret == -2)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (ret == -1)
	{
		ft_putstr_fd("stdin: Interrupted system call\n", 2);
		if (shell->envv && shell->envv[0])
		{
			free_table(shell->envv);
			shell->envv = env_to_tab(shell->list);
		}
		return (-1);
	}
	return (1);
}

static void	display_prompt(char **line, int *status, t_shell *shell)
{
	int			ret;
	t_env		*tmp;

	*status = 1;
	tmp = shell->list;
	ft_putstr(C01);
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PWD") == 0)
		{
			ft_putstr(tmp->val);
			break ;
		}
		tmp = tmp->next;
	}
	ft_putstr(RESET);
	ft_putstr(C05);
	ft_putstr(" @$h >");
	ft_putstr(RESET);
	ft_putchar(' ');
	ret = get_next_line(0, line);
	if (cmd_d(ret, shell) == -1)
	{
		if (*line && *line[0])
			ft_strdel(line);
		*status = 2;
	}
}

void		ash_loop(t_shell *shell)
{
	int		status;
	char	*line;

	display_prompt(&line, &status, shell);
	if (line && line[0])
	{
		status = (ft_strchr(line, ';')) ?
			semicol_loop(shell, line) : no_semi_loop(shell, line);
	}
	if (line)
		ft_strdel(&line);
	while (status)
	{
		display_prompt(&line, &status, shell);
		if (line && line[0])
		{
			status = (ft_strchr(line, ';')) ?
				semicol_loop(shell, line) : no_semi_loop(shell, line);
		}
		if (line)
			ft_strdel(&line);
	}
}
