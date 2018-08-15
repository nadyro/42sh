/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 06:09:10 by azybert           #+#    #+#             */
/*   Updated: 2018/08/15 15:49:29 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static t_node	*find_in_history(char *cmd, t_node *history, int *depth)
{
	t_node	*check_depth;

	check_depth = NULL;
	if (history == NULL)
		return (NULL);
	else if (ft_strstr(history->cmd, cmd) != NULL)
	{
		if (*depth > 1)
		{
			*depth = *depth - 1;
			check_depth = find_in_history(cmd, history->next, depth);
			*depth = *depth + 1;
		}
		if (check_depth)
			return (check_depth);
		else
		{
			*depth = 1;
			return (history);
		}
	}
	else
		return (find_in_history(cmd, history->next, depth));
}

static void		search_display(t_g_prpt *g_prpt, char *cmd_found)
{
	char	*to_display;
	char	*to_free;
	char	*cmd_search;

	to_display = NULL;
	move_cursor(g_prpt, 0, true);
	to_display = ft_strjoin(g_prpt->line, "\nHistory: ");
	to_free = to_display;
	to_display = (cmd_found ? ft_strjoin(to_display, cmd_found) : to_display);
	cmd_search = g_prpt->line;
	g_prpt->line = to_display;
	g_prpt->total = ft_strlen(g_prpt->line);
	tputs(tgetstr("cd", NULL), 0, ft_putshit);
	write_data(g_prpt, g_prpt->line, g_prpt->total);
	free(to_free);
	to_free = NULL;
	if (cmd_found)
		free(to_display);
	g_prpt->line = cmd_search;
	g_prpt->total = ft_strlen(g_prpt->line);
	move_cursor(g_prpt, g_prpt->total, true);
}

static int		search_react(t_g_prpt *g_prpt)
{
	char	user_entry[7];
	int		nb_user_entry;

	ft_bzero(user_entry, 7);
	nb_user_entry = read(0, user_entry, 6);
	if (nb_user_entry == 3 && user_entry[0] == 27)
		return (user_entry[2] == 65 ? 2 : 3);
	else if (user_entry[0] == 27 || g_prpt->end == 1)
		return (-1);
	else if (user_entry[0] == 12)
	{
		tputs(tgetstr("cl", NULL), 0, ft_putshit);
		write(1, g_prpt->disp, ft_strlen(g_prpt->disp));
		g_prpt->origin->y = 0;
	}
	else if (user_entry[0] == 127 && g_prpt->total > 0)
		g_prpt_delete(g_prpt);
	else
	{
		((g_prpt->buf = ft_strdup(user_entry)) != NULL ? 0 : exit(1));
		if (nb_user_entry == 6)
			ft_flush(g_prpt);
		return (data_react(g_prpt) ? 1 : 0);
	}
	return (0);
}

static void		search_mode_aux(t_g_prpt *g_prpt, t_stat_data *stat_data)
{
	int		loop_state;
	int		depth;
	t_node	*found;

	loop_state = 0;
	depth = 1;
	while (loop_state == 0)
	{
		found = find_in_history(g_prpt->line, g_prpt->history, &depth);
		search_display(g_prpt, (found ? found->cmd : NULL));
		loop_state = search_react(g_prpt);
		if (loop_state == 2 || loop_state == 3)
		{
			(loop_state == 2 ? depth++ : 0);
			(loop_state == 3 && depth > 1 ? depth-- : 0);
			loop_state = 0;
		}
		else
			depth = 1;
	}
	ft_strdel(&g_prpt->line);
	move_cursor(g_prpt, 0, true);
	g_prpt->total = 0;
	secure_stock(g_prpt, (loop_state == 1 && found
		? found->cmd : stat_data->old_line));
}

void			search_mode(t_g_prpt *g_prpt, t_stat_data *stat_data)
{
	if (stat_data->old_line)
	{
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	stat_data->old_line = g_prpt->line;
	((g_prpt->line = ft_strdup("\0")) ? 0 : exit(1));
	search_mode_aux(g_prpt, stat_data);
	ft_strdel(&stat_data->old_line);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	(g_prpt->end ? termanip(33) : 0);
	g_prpt->end = 0;
}
