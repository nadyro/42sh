/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cursor_motion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:42:41 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:36 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	ft_cursor_up(t_g_prpt *g_prpt)
{
	size_t	tmp;
	size_t	tmp2;
	size_t	loop;

	if (ft_strchr(g_prpt->line, '\n'))
	{
		loop = -1;
		tmp2 = (ft_add_nl(g_prpt, g_prpt->pos) + g_prpt->origin->x) %
			g_prpt->size->x;
		while (++loop < g_prpt->size->x && loop != g_prpt->pos)
			if (g_prpt->line[g_prpt->pos - loop] == '\n' && loop != 0)
			{
				tmp = (ft_add_nl(g_prpt, g_prpt->pos - loop) +
						g_prpt->origin->x) % g_prpt->size->x;
				if (tmp > tmp2)
					tmp = g_prpt->pos - tmp - 1;
				else
					tmp = g_prpt->pos - tmp2 - 1;
				loop = g_prpt->size->x;
			}
	}
	else
		tmp = g_prpt->pos - g_prpt->size->x;
	(tmp < g_prpt->pos ?
		move_cursor(g_prpt, tmp, true) : move_cursor(g_prpt, 0, true));
}

void	ft_cursor_down(t_g_prpt *g_prpt)
{
	size_t	tmp;
	size_t	loop;

	if (ft_strchr(g_prpt->line, '\n'))
	{
		loop = -1;
		while (++loop < g_prpt->size->x && g_prpt->line[g_prpt->pos + loop])
		{
			if (g_prpt->line[g_prpt->pos + loop] == '\n')
			{
				tmp = g_prpt->pos + loop + 1 + ((ft_add_nl(g_prpt, g_prpt->pos)
							+ g_prpt->origin->x) % g_prpt->size->x);
				if ((g_prpt->origin->y + (g_prpt->origin->x +
							ft_add_nl(g_prpt, tmp)) / g_prpt->size->x) - 1 !=
						(g_prpt->origin->y + (g_prpt->origin->x +
							ft_add_nl(g_prpt, g_prpt->pos)) / g_prpt->size->x))
					tmp = ft_strchr(&g_prpt->line[g_prpt->pos + loop + 1], '\n')
						- &g_prpt->line[0];
				loop = g_prpt->size->x;
			}
		}
	}
	else
		tmp = g_prpt->pos + g_prpt->size->x;
	(tmp <= g_prpt->total ? move_cursor(g_prpt, tmp, true) : 0);
}

void	ft_cursor_word_left(t_g_prpt *g_prpt)
{
	if (g_prpt->pos != g_prpt->total ||
			ft_isspace(g_prpt->line[g_prpt->pos - 1]))
		while (g_prpt->pos > 0 &&
				!(ft_isspace(g_prpt->line[g_prpt->pos])))
			g_prpt->pos--;
	while (g_prpt->pos > 0 &&
			ft_isspace(g_prpt->line[g_prpt->pos]))
		g_prpt->pos--;
	while (g_prpt->pos > 0 &&
			!(ft_isspace(g_prpt->line[g_prpt->pos])))
		g_prpt->pos--;
	if (g_prpt->pos != 0)
		g_prpt->pos++;
	move_cursor(g_prpt, g_prpt->pos, true);
}

void	ft_cursor_word_right(t_g_prpt *g_prpt)
{
	while (g_prpt->pos < g_prpt->total &&
			!(ft_isspace(g_prpt->line[g_prpt->pos])))
		g_prpt->pos++;
	while (g_prpt->pos < g_prpt->total &&
			ft_isspace(g_prpt->line[g_prpt->pos]))
		g_prpt->pos++;
	move_cursor(g_prpt, g_prpt->pos, true);
}
