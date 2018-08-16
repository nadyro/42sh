/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:39:16 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 18:41:50 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"
#include "builtins.h"

void		secure_stock(t_g_prpt *g_prpt, char *to_stock)
{
	int		mem;

	if (g_prpt->line == NULL)
		if (!(g_prpt->line = ft_strdup("\0")))
			sh_close(1, "");
	if (to_stock == NULL || to_stock[0] == '\0')
		return ;
	mem = 0;
	while (to_stock[mem])
		g_prpt_stock(g_prpt, &to_stock[mem++]);
}

void		sig_react(t_g_prpt *g_prpt, char c)
{
	if (c == 4 && g_prpt->total == 0)
		termanip(-1);
	else if (c == 12)
		term_clear();
}

int			data_react(t_g_prpt *g_prpt)
{
	int		mem;
	char	*to_free;

	mem = 0;
	while (ft_isprint(g_prpt->buf[mem]))
		g_prpt_stock(g_prpt, &g_prpt->buf[mem++]);
	if (g_prpt->buf[mem] == '\n')
	{
		move_cursor(g_prpt, g_prpt->total, true);
		g_prpt_stock(g_prpt, &g_prpt->buf[mem]);
		to_free = g_prpt->buf;
		if (!(g_prpt->buf = ft_strdup(&g_prpt->buf[mem + 1])))
			sh_close(1, "");
		free(to_free);
		tputs(tgetstr("ce", NULL), 1, ft_putshit);
		return (1);
	}
	free(g_prpt->buf);
	g_prpt->buf = NULL;
	return (0);
}

static void	esc_react_aux(t_g_prpt *g_prpt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data)
{
	if (nb_user_entry == 3 && user_entry[2] == 65)
		history_next(g_prpt, stat_data);
	else if (nb_user_entry == 3 && user_entry[2] == 66)
		history_prev(g_prpt, stat_data);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'S' && g_prpt->total > 0)
		selection_mode(g_prpt, stat_data);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'V' && stat_data->copied != NULL)
		secure_stock(g_prpt, stat_data->copied);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'R' && g_prpt->history)
		search_mode(g_prpt, stat_data);
	else if (nb_user_entry == 1 && user_entry[0] == 9)
		auto_complete(g_prpt);
}

void		esc_react(t_g_prpt *g_prpt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data)
{
	if (nb_user_entry == 1 && user_entry[0] == 127 && g_prpt->pos > 0)
		g_prpt_delete(g_prpt);
	else if (nb_user_entry == 4 && user_entry[3] == 126 &&
			g_prpt->pos < g_prpt->total)
		g_prpt_backdel(g_prpt);
	else if (nb_user_entry == 3 && user_entry[2] == 68 && g_prpt->pos > 0)
		move_cursor(g_prpt, g_prpt->pos - 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 67 &&
			g_prpt->pos < g_prpt->total)
		move_cursor(g_prpt, g_prpt->pos + 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 72)
		move_cursor(g_prpt, 0, true);
	else if (nb_user_entry == 3 && user_entry[2] == 70)
		move_cursor(g_prpt, g_prpt->total, true);
	else if (nb_user_entry == 6 && user_entry[5] == 68)
		ft_cursor_word_left(g_prpt);
	else if (nb_user_entry == 6 && user_entry[5] == 67)
		ft_cursor_word_right(g_prpt);
	else if (nb_user_entry == 6 && user_entry[5] == 65)
		ft_cursor_up(g_prpt);
	else if (nb_user_entry == 6 && user_entry[5] == 66)
		ft_cursor_down(g_prpt);
	else
		esc_react_aux(g_prpt, nb_user_entry, user_entry, stat_data);
}
