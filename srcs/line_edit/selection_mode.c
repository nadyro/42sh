/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 22:38:46 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:35 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	selection_delete(t_g_prpt *g_prpt, size_t start_pos)
{
	int	loop;

	if (start_pos > g_prpt->pos)
	{
		loop = start_pos - g_prpt->pos + 1;
		while (loop--)
			g_prpt_backdel(g_prpt);
	}
	else
	{
		loop = g_prpt->pos - start_pos;
		if (loop)
			g_prpt_backdel(g_prpt);
		while (loop--)
			g_prpt_delete(g_prpt);
	}
	return ;
}

static void	selection_write(t_g_prpt *g_prpt, size_t start_pos)
{
	size_t	mem_pos;
	size_t	size;

	mem_pos = g_prpt->pos;
	move_cursor(g_prpt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	size = (start_pos > mem_pos ? mem_pos : start_pos);
	write_data(g_prpt, g_prpt->line, size);
	move_cursor(g_prpt, size, true);
	tputs(tgetstr("mr", NULL), 1, ft_putshit);
	write_data(g_prpt, g_prpt->line + g_prpt->pos,
			(start_pos > mem_pos ?
			start_pos - mem_pos + 1 : mem_pos - start_pos));
	tputs(tgetstr("me", NULL), 1, ft_putshit);
	move_cursor(g_prpt, (start_pos > mem_pos ? start_pos + 1 : mem_pos), true);
	size = g_prpt->total - g_prpt->pos;
	write_data(g_prpt, g_prpt->line + g_prpt->pos, size);
	move_cursor(g_prpt, mem_pos, true);
}

static int	selection_tree_aux(t_g_prpt *g_prpt, t_stat_data *stat_data,
		char *user_entry, size_t start_pos)
{
	if (user_entry[0] == 'c' || user_entry[0] == 'x')
	{
		free(stat_data->copied);
		stat_data->copied = (start_pos > g_prpt->pos ?
				ft_strndup(g_prpt->line + g_prpt->pos,
					start_pos - g_prpt->pos + 1) :
				ft_strndup(g_prpt->line + start_pos,
					g_prpt->pos - start_pos + 1));
		selection_write(g_prpt, g_prpt->pos);
		if (user_entry[0] == 'x')
			selection_delete(g_prpt, start_pos);
	}
	else if (user_entry[0] == 127)
		selection_delete(g_prpt, start_pos);
	else if (user_entry[0] == 27 || g_prpt->end == 1)
		selection_write(g_prpt, g_prpt->pos);
	else
		return (0);
	handle_sig();
	(g_prpt->end ? termanip(33) : 0);
	g_prpt->end = 0;
	return (1);
}

static int	selection_tree(t_g_prpt *g_prpt, int nb_user_entry,
		char *user_entry)
{
	if (nb_user_entry == 3 && user_entry[2] == 65)
		ft_cursor_up(g_prpt);
	else if (nb_user_entry == 3 && user_entry[2] == 66)
		ft_cursor_down(g_prpt);
	else if (nb_user_entry == 3 && user_entry[2] == 68)
		(g_prpt->pos > 0 ? move_cursor(g_prpt, g_prpt->pos - 1, true) : 0);
	else if (nb_user_entry == 3 && user_entry[2] == 67 &&
			g_prpt->pos < g_prpt->total)
		(g_prpt->pos < g_prpt->total - 1 ?
		move_cursor(g_prpt, g_prpt->pos + 1, true) : 0);
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
		return (1);
	return (0);
}

void		selection_mode(t_g_prpt *g_prpt, t_stat_data *stat_data)
{
	char	user_entry[7];
	size_t	start_pos;
	int		nb_user_entry;

	ignore_handle();
	g_prpt->pos += (g_prpt->pos == g_prpt->total ? -1 : 0);
	start_pos = g_prpt->pos;
	while (1)
	{
		selection_write(g_prpt, start_pos);
		ft_bzero(user_entry, 7);
		nb_user_entry = read(0, user_entry, 6);
		if (user_entry[0] == 12)
		{
			tputs(tgetstr("cl", NULL), 0, ft_putshit);
			write(1, g_prpt->disp, ft_strlen(g_prpt->disp));
			g_prpt->origin->y = 0;
		}
		(nb_user_entry == 6 ? ft_flush(g_prpt) : 0);
		(g_prpt->buf ? ft_strdel(&g_prpt->buf) : 0);
		if (selection_tree(g_prpt, nb_user_entry, user_entry))
			if (selection_tree_aux(g_prpt, stat_data, user_entry, start_pos))
				return ;
	}
}
