/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 21:29:08 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"
#include "builtins.h"

t_node		*add_to_history(char *cmd, t_node *history)
{
	t_node	*new;
	char	*check;

	check = NULL;
	if (cmd == NULL || ft_strlen((check = ft_strtrim(cmd))) == 0)
	{
		free(check);
		return (history);
	}
	free(check);
	if (!(new = malloc(sizeof(*new))))
		sh_close(1, "");
	if (!(new->cmd = ft_strdup(cmd)))
		sh_close(1, "");
	new->next = history;
	new->prev = NULL;
	if (history)
		history->prev = new;
	history = new;
	if (ft_strchr(history->cmd, '\n'))
		if (*(ft_strrchr(history->cmd, '\n') + 1) == '\0')
			*(ft_strrchr(history->cmd, '\n')) = '\0';
	return (history);
}

static void	ft_norme(t_g_prpt *g_prpt)
{
	free(g_prpt->line);
	g_prpt->line = NULL;
	g_prpt->total = 0;
	move_cursor(g_prpt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
}

void		history_next(t_g_prpt *g_prpt, t_stat_data *s_d)
{
	if (g_prpt->history == NULL)
		return ;
	if (g_prpt->current == NULL)
	{
		g_prpt->current = g_prpt->history;
		if (g_prpt->line && ft_strlen(g_prpt->line))
		{
			free(s_d->old_line);
			((s_d->old_line = ft_strdup(g_prpt->line)) ? 0 : sh_close(0, ""));
		}
	}
	else if (g_prpt->current->next != NULL)
	{
		if (ft_strcmp(g_prpt->line, g_prpt->current->cmd))
		{
			free(s_d->old_line);
			((s_d->old_line = ft_strdup(g_prpt->line)) ? 0 : sh_close(0, ""));
		}
		g_prpt->current = g_prpt->current->next;
	}
	else
		return ;
	ft_norme(g_prpt);
	secure_stock(g_prpt, g_prpt->current->cmd);
}

void		history_prev(t_g_prpt *g_prpt, t_stat_data *stat_data)
{
	if (g_prpt->current == NULL)
		return ;
	if (ft_strcmp(g_prpt->line, g_prpt->current->cmd))
	{
		free(stat_data->old_line);
		((stat_data->old_line = ft_strdup(g_prpt->line)) ? 0 : sh_close(0, ""));
	}
	g_prpt->current = g_prpt->current->prev;
	ft_norme(g_prpt);
	if (g_prpt->current)
		secure_stock(g_prpt, g_prpt->current->cmd);
	else
	{
		secure_stock(g_prpt, stat_data->old_line);
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
}
