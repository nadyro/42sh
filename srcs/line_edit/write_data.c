/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:19:56 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:31 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	ft_writenl(char *to_display, size_t tmp)
{
	size_t	k;
	size_t	sp;

	k = 0;
	sp = 0;
	while (sp + k < tmp)
	{
		if (to_display[sp + k] == '\n')
		{
			write(1, &to_display[sp], k + 1);
			write(1, "\r", 1);
			sp = sp + k + 1;
			k = 0;
		}
		else
			k++;
	}
	write(1, &to_display[sp], k + 1);
	write(1, "\r", 1);
}

static void	write_data_aux(t_g_prpt *g_prpt, char *to_display, size_t size)
{
	size_t	tmp;
	size_t	displayed;

	displayed = g_prpt->total - ft_strlen(to_display);
	while (size != 0)
	{
		move_cursor(g_prpt, displayed, false);
		tputs(tgetstr("ce", NULL), 1, ft_putshit);
		tmp = g_prpt->size->x - (ft_add_nl(g_prpt, displayed) +
				g_prpt->origin->x) % g_prpt->size->x;
		tmp = ((tmp > size) ? size : tmp);
		ft_writenl(to_display, tmp);
		displayed = displayed + tmp;
		to_display += tmp;
		size -= tmp;
	}
}

void		write_data(t_g_prpt *g_prpt, char *to_display, size_t size)
{
	if (g_prpt->origin->y == 0xffffffffffffffff)
		return ;
	move_cursor(g_prpt, g_prpt->pos, true);
	while (g_prpt->size->y <= g_prpt->origin->y + (g_prpt->origin->x +
				ft_add_nl(g_prpt, g_prpt->pos + size)) / g_prpt->size->x)
	{
		move_cursor(g_prpt, (g_prpt->size->y - g_prpt->origin->y) *
				g_prpt->size->x, false);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
		g_prpt->origin->y--;
	}
	if (g_prpt->origin->y == 0xffffffffffffffff)
		return ;
	write_data_aux(g_prpt, to_display, size);
}
